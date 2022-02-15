//#include "main.h"
//#include "renderer.h"
//#include "manager.h"
//#include "scene.h"
//#include "explosion.h"
//#include "camera.h"
//
//void Explosion::Init()
//{
//	VERTEX_3D vertex[4];
//
//	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
//	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
//
//	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
//	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
//
//	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
//	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
//
//	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
//	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
//
//	//頂点バッファ生成
//	D3D11_BUFFER_DESC bd;
//	ZeroMemory(&bd, sizeof(bd));
//	bd.Usage = D3D11_USAGE_DYNAMIC;//頂点バッファの書き換えができるように
//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;//頂点バッファの書き換えができるように
//	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//頂点バッファの書き換えができるように
//	//これを変えなくてもエラーは出ないけど実行するとできない
//
//	D3D11_SUBRESOURCE_DATA sd;
//	ZeroMemory(&sd, sizeof(sd));
//	sd.pSysMem = vertex;
//
//	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);
//
//	//テクスチャ読み込み
//	D3DX11CreateShaderResourceViewFromFile
//	(
//		Renderer::GetDevice(),
//		"asset/texture/explosion.png",
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
//	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");//ライティング無効
//	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");//ライティング無効
//
//
//	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//
//	count = 0;
//}
//
//void Explosion::Uninit()
//{
//	VertexBuffer->Release();
//	Texture->Release();
//
//	VertexLayout->Release();
//	VertexShader->Release();
//	PixelShader->Release();
//}
//
//void Explosion::Update()
//{
//	count++;
//	if (count >= 16)
//	{
//		SetDestroy();
//		return;
//	}
//}
//
//void Explosion::Draw()
//{
//	//テクスチャ座標算出
//	float x = count % 4 * (1.0f / 4);
//	float y = count / 4 * (1.0f / 4);
//
//	//頂点データ書き換え
//	D3D11_MAPPED_SUBRESOURCE msr;
//	Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
//
//	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
//
//	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
//	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[0].TexCoord = D3DXVECTOR2(x, y);
//
//	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
//	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[1].TexCoord = D3DXVECTOR2(x + 0.25f, y);
//
//	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
//	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[2].TexCoord = D3DXVECTOR2(x, y + 0.25f);
//
//	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
//	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[3].TexCoord = D3DXVECTOR2(x + 0.25f, y + 0.25f);
//
//	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);
//
//	//入力レイアウト設定
//	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);
//
//	//シェーダ設定
//	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
//	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);
//
//	//カメラのビューマトリクス取得
//	Scene* scene = Manager::GetScene();
//	Camera* camera = scene->GetObj<Camera>(0);
//	D3DXMATRIX view = camera->GetViewMatrix();
//
//	//ビューの逆行列
//	D3DXMATRIX invView;
//	D3DXMatrixInverse(&invView, NULL, &view);//逆行列
//	invView._41 = 0.0f;
//	invView._42 = 0.0f;
//	invView._43 = 0.0f;
//	//移動を0.0fにしている
//
//	//ワールドマトリクス設定
//	D3DXMATRIX world, sca, trans;
//	D3DXMatrixScaling(&sca, scale.x, scale.y, scale.z);
//	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);
//	world = sca * invView * trans;	//マルチプライという計算で合成
//	Renderer::SetWorldMatrix(&world);
//
//	//頂点バッファ設定
//	UINT stride = sizeof(VERTEX_3D);
//	UINT offset = 0;
//	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
//
//	//マテリアル設定
//	MATERIAL material;
//	ZeroMemory(&material, sizeof(material));
//	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	Renderer::SetMaterial(material);
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
