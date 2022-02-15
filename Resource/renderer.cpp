
#include "main.h"
#include "renderer.h"
#include <io.h>


D3D_FEATURE_LEVEL       Renderer::FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           Renderer::Device = NULL;
ID3D11DeviceContext*    Renderer::DeviceContext = NULL;
IDXGISwapChain*         Renderer::SwapChain = NULL;
ID3D11RenderTargetView* Renderer::RenderTargetView = NULL;
ID3D11DepthStencilView* Renderer::DepthStencilView = NULL;

ID3D11Buffer*			Renderer::WorldBuffer = NULL;
ID3D11Buffer*			Renderer::ViewBuffer = NULL;
ID3D11Buffer*			Renderer::ProjectionBuffer = NULL;
ID3D11Buffer*			Renderer::MaterialBuffer = NULL;
ID3D11Buffer*			Renderer::LightBuffer = NULL;


ID3D11DepthStencilState* Renderer::DepthStateEnable = NULL;
ID3D11DepthStencilState* Renderer::DepthStateDisable = NULL;





void Renderer::Init()
{
	HRESULT hr = S_OK;




	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = GetWindow();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										0,
										NULL,
										0,
										D3D11_SDK_VERSION,
										&swapChainDesc,
										&SwapChain,
										&Device,
										&FeatureLevel,
										&DeviceContext );






	// レンダーターゲットビュー作成
	ID3D11Texture2D* renderTarget = NULL;
	SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&renderTarget );
	Device->CreateRenderTargetView( renderTarget, NULL, &RenderTargetView );
	renderTarget->Release();


	// デプスステンシルバッファ作成
	//奥行きを描画するためのやつ
	ID3D11Texture2D* depthStencile = NULL;
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &DepthStencilView);
	depthStencile->Release();


	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);





	// ビューポート設定
	//画面分割に使える
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	DeviceContext->RSSetViewports( 1, &viewport );



	// ラスタライザステート設定
	//描画の設定。塗りつぶすのか、カリングなど
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID; 
	rasterizerDesc.CullMode = D3D11_CULL_BACK; 
	rasterizerDesc.DepthClipEnable = TRUE; 
	rasterizerDesc.MultisampleEnable = FALSE; 

	ID3D11RasterizerState *rs;
	Device->CreateRasterizerState( &rasterizerDesc, &rs );

	DeviceContext->RSSetState( rs );




	// ブレンドステート設定
	//αブレンドの設定
	//半透明、加算合成とかの
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	ID3D11BlendState* blendState = NULL;
	Device->CreateBlendState( &blendDesc, &blendState );
	DeviceContext->OMSetBlendState( blendState, blendFactor, 0xffffffff );



	// デプスステンシルステート設定
	//震度バッファとか
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	Device->CreateDepthStencilState( &depthStencilDesc, &DepthStateEnable );//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ZERO;
	Device->CreateDepthStencilState( &depthStencilDesc, &DepthStateDisable );//深度無効ステート

	DeviceContext->OMSetDepthStencilState( DepthStateEnable, NULL );




	// サンプラーステート設定
	//テクスチャをどうやって貼り付けるか
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	ID3D11SamplerState* samplerState = NULL;
	Device->CreateSamplerState( &samplerDesc, &samplerState );

	DeviceContext->PSSetSamplers( 0, 1, &samplerState );



	// 定数バッファ生成
	//シェーダー
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	Device->CreateBuffer( &bufferDesc, NULL, &WorldBuffer );
	DeviceContext->VSSetConstantBuffers( 0, 1, &WorldBuffer);

	Device->CreateBuffer( &bufferDesc, NULL, &ViewBuffer );
	DeviceContext->VSSetConstantBuffers( 1, 1, &ViewBuffer );

	Device->CreateBuffer( &bufferDesc, NULL, &ProjectionBuffer );
	DeviceContext->VSSetConstantBuffers( 2, 1, &ProjectionBuffer );


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	Device->CreateBuffer( &bufferDesc, NULL, &MaterialBuffer );
	DeviceContext->VSSetConstantBuffers( 3, 1, &MaterialBuffer );


	bufferDesc.ByteWidth = sizeof(LIGHT);

	Device->CreateBuffer( &bufferDesc, NULL, &LightBuffer );
	DeviceContext->VSSetConstantBuffers( 4, 1, &LightBuffer );
	DeviceContext->PSSetConstantBuffers(4, 1, &LightBuffer);





	// ライト初期化
	LIGHT light{};
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetLight(light);



	// マテリアル初期化
	MATERIAL material{};
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);




}



void Renderer::Uninit()
{
	//必要なくなったメソッドはリリースしないといけない
	//マクロを使ってるといらない？
	WorldBuffer->Release();
	ViewBuffer->Release();
	ProjectionBuffer->Release();
	LightBuffer->Release();
	MaterialBuffer->Release();


	DeviceContext->ClearState();
	RenderTargetView->Release();
	SwapChain->Release();
	DeviceContext->Release();
	Device->Release();

}




void Renderer::Begin()
{
	//float clearColor[4] = { 0.973f, 0.855f, 0.847f, 1.0f };	//色をクリアしたときの色を変えるとこ
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	//色をクリアしたときの色を変えるとこ
	DeviceContext->ClearRenderTargetView( RenderTargetView, clearColor );
	DeviceContext->ClearDepthStencilView( DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}



void Renderer::End()
{
	SwapChain->Present( 1, 0 );
}




void Renderer::SetDepthEnable( bool Enable )
{
	if( Enable )
		DeviceContext->OMSetDepthStencilState( DepthStateEnable, NULL );
	else
		DeviceContext->OMSetDepthStencilState( DepthStateDisable, NULL );

}

void Renderer::SetWorldViewProjection2D()
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);

	DeviceContext->UpdateSubresource(WorldBuffer, 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	DeviceContext->UpdateSubresource(ViewBuffer, 0, NULL, &view, 0, 0);

	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&projection, &projection);
	DeviceContext->UpdateSubresource( ProjectionBuffer, 0, NULL, &projection, 0, 0 );

}


void Renderer::SetWorldMatrix( D3DXMATRIX* WorldMatrix )
{
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	DeviceContext->UpdateSubresource(WorldBuffer, 0, NULL, &world, 0, 0);
}

void Renderer::SetViewMatrix( D3DXMATRIX* ViewMatrix )
{
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	DeviceContext->UpdateSubresource(ViewBuffer, 0, NULL, &view, 0, 0);
}

void Renderer::SetProjectionMatrix( D3DXMATRIX* ProjectionMatrix )
{
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	DeviceContext->UpdateSubresource(ProjectionBuffer, 0, NULL, &projection, 0, 0);
}



void Renderer::SetMaterial( MATERIAL Material )
{
	DeviceContext->UpdateSubresource( MaterialBuffer, 0, NULL, &Material, 0, 0 );
}

void Renderer::SetLight( LIGHT Light )
{
	DeviceContext->UpdateSubresource(LightBuffer, 0, NULL, &Light, 0, 0);
}





void Renderer::CreateVertexShader( ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName )
{

	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	Device->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}



void Renderer::CreatePixelShader( ID3D11PixelShader** PixelShader, const char* FileName )
{
	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}


