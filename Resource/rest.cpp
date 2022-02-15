
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "rest.h"
#include "input.h"
#include "scene.h"

#include "ledgerLine.h"

static D3D11_BUFFER_DESC bd{};
static D3D11_SUBRESOURCE_DATA sd{};


void Rest::Init()
{
	//休符テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile
	(//全休符
		Renderer::GetDevice(),
		"asset/texture/whole-rest.png",
		NULL,
		NULL,
		&RestTexture[whole],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//２分休符
		Renderer::GetDevice(),
		"asset/texture/half-rest.png",
		NULL,
		NULL,
		&RestTexture[half],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//４分休符
		Renderer::GetDevice(),
		"asset/texture/quarter-rest.png",
		NULL,
		NULL,
		&RestTexture[quarter],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//８分休符
		Renderer::GetDevice(),
		"asset/texture/eighth-rest.png",
		NULL,
		NULL,
		&RestTexture[eighth],
		NULL
	);


	//レンダラークラスの中に作ってある関数を使ってる
	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	position = { 0.0f,130.0f,0.0f };
	scale = { 190.0f,190.0f,0.0f };

	tex[0] = { 0.0f, 0.0f };
	tex[1] = { 1.0f, 0.0f };
	tex[2] = { 0.0f, 1.0f };
	tex[3] = { 1.0f, 1.0f };

}

void Rest::Uninit()
{
	VertexBuffer->Release();
	Texture->Release();

	VertexLayout->Release();
	VertexShader->Release();
	PixelShader->Release();
}

void Rest::Update()
{

}

void Rest::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void Rest::Set(int type, D3DXVECTOR3 pos)
{
	switch (type)
	{
	case whole:
		Texture = RestTexture[whole];
		break;

	case half:
		Texture = RestTexture[half];
		break;

	case quarter:
		Texture = RestTexture[quarter];
		break;

	case eighth:
		Texture = RestTexture[eighth];
		break;

	default:
		break;
	}

	position = pos;

	//頂点データ
	restVertex[0] = { D3DXVECTOR3(position.x          , position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[0].x, tex[0].y) };
	restVertex[1] = { D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[1].x, tex[1].y) };
	restVertex[2] = { D3DXVECTOR3(position.x          , position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[2].x, tex[2].y) };
	restVertex[3] = { D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[3].x, tex[3].y) };

	//頂点バッファ生成
	//D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = restVertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

}
