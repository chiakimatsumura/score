
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "ledgerLine.h"
#include "input.h"
#include "scene.h"
#include "note.h"
#include "effect.h"
#include "audio.h"
static D3D11_BUFFER_DESC bd{};
static D3D11_SUBRESOURCE_DATA sd{};

void LedgerLine::Init()
{
	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile
	(
		Renderer::GetDevice(),
		"asset/texture/ledger-line.png",
		NULL,
		NULL,
		&Texture,
		NULL
	);

	assert(Texture);	//エラーを処理するための仕組み
	//デバッグ実行のときにテクスチャが読み込めたかをチェックしてくれる

	//	//頂点データ
	//VERTEX_3D vertex[] =
	//{
	//	{D3DXVECTOR3(position.x,           position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
	//	{D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
	//	{D3DXVECTOR3(position.x,           position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
	//	{D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)}
	//};

	////頂点バッファ生成
	//D3D11_BUFFER_DESC bd{};
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd{};
	//sd.pSysMem = vertex;

	//Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);


	//レンダラークラスの中に作ってある関数を使ってる
	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Scene* scene = Manager::GetScene();

	_noteSE = scene->AddObject<Audio>(2);
	_noteSE->Load("asset\\sound\\se\\note.wav");

	position = { 0.0f,130.0f,0.0f };
	scale = { 190.0f,190.0f,0.0f };
}

void LedgerLine::Uninit()
{
	VertexBuffer->Release();
	Texture->Release();

	VertexLayout->Release();
	VertexShader->Release();
	PixelShader->Release();
}

void LedgerLine::Update()
{
	//if (Input::GetKeyTrigger('W'))
	//{
	//	position.y -= 11.0f;
	//}
	//
	//if (Input::GetKeyTrigger('S'))
	//{
	//	position.y += 11.0f;
	//}

	//if (position.y <= C1)
	//{
	//	position.y = C1;
	//}

	//if (position.y >= C)
	//{
	//	position.y = C;
	//}

	//if (position.y < C)
	//{
	//	SetDestroy();//消す予約
	//}

	//Scene* scene = Manager::GetScene();
	//std::vector<Note*>noteList = scene->GetObjects<Note>(1);//音符の情報を取得

	////if (Input::GetKeyTrigger(VK_SPACE))
	//{
	//	for (Note* note : noteList)
	//	{//音符との当たり判定
	//		D3DXVECTOR3 notePosition = note->GetPosition();

	//		if (position.x + 170.0f >= notePosition.x && position.x + 120.0f <= notePosition.x && position.y == notePosition.y)
	//		{//プレイヤーと音符があたっているか
	//			if (Input::GetKeyTrigger(VK_SPACE))
	//			{//スペースキーを押したら
	//				scene->AddObject<Effect>(1)->SetPosition(notePosition);//エフェクト表示

	//				//_noteSE->Play();

	//				note->SetDestroy();

	//				return;
	//			}
	//		}
	//	}
	//}
}

void LedgerLine::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//頂点データ
	VERTEX_3D vertex[] =
	{
		{D3DXVECTOR3(position.x,           position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
		{D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
		{D3DXVECTOR3(position.x,           position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
		{D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)}
	};

	//頂点バッファ生成
	//D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

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
