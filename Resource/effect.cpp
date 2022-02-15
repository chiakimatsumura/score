//
//#include "main.h"
//#include "renderer.h"
//#include "effect.h"
//
//
//void Effect::Init()
//{
//	//テクスチャ読み込み
//	D3DX11CreateShaderResourceViewFromFile
//	(
//		Renderer::GetDevice(),
//		"asset/texture/effect.png",
//		NULL,
//		NULL,
//		&Texture,
//		NULL
//	);
//
//	assert(Texture);	//エラーを処理するための仕組み
//	//デバッグ実行のときにテクスチャが読み込めたかをチェックしてくれる
//
//	//レンダラークラスの中に作ってある関数を使ってる
//	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
//	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");
//
//	position = { 0.0f,0.0f,0.0f };
//	scale = { 300.0f,300.0f,0.0f };
//	rotation = { 0.0f,0.0f,0.0f };
//}
//
//void Effect::Uninit()
//{
//	VertexBuffer->Release();
//	Texture->Release();
//
//	VertexLayout->Release();
//	VertexShader->Release();
//	PixelShader->Release();
//}
//
//void Effect::Update()
//{
//	rotation.x += 8.0f;
//	rotation.y += 8.0f;
//	count++;
//	if (count >= 13)
//	{
//		SetDestroy();
//		return;
//	}
//}
//
//void Effect::Draw()
//{
//	//入力レイアウト設定
//	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);
//
//	//シェーダ設定
//	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
//	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);
//
//	//マトリクス設定
//	Renderer::SetWorldViewProjection2D();
//
//	//頂点データ
//	VERTEX_3D vertex[] =
//	{
//		{D3DXVECTOR3(position.x           + rotation.x, position.y           - rotation.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
//		{D3DXVECTOR3(position.x + scale.x + rotation.x, position.y           + rotation.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
//		{D3DXVECTOR3(position.x           - rotation.x, position.y + scale.y - rotation.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
//		{D3DXVECTOR3(position.x + scale.x - rotation.x, position.y + scale.y + rotation.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)}
//	};
//
//	//頂点バッファ生成
//	D3D11_BUFFER_DESC bd{};
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//
//	D3D11_SUBRESOURCE_DATA sd{};
//	sd.pSysMem = vertex;
//
//	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);
//
//	//頂点バッファ設定
//	UINT stride = sizeof(VERTEX_3D);
//	UINT offset = 0;
//	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
//
//	//テクスチャ設定
//	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);
//
//	//プリミティブトポロジ設定
//	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	//ポリゴン描画
//	Renderer::GetDeviceContext()->Draw(4, 0);
//}
