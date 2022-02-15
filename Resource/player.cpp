
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "player.h"
#include "input.h"
#include "scene.h"
#include "note.h"
#include "effect.h"
#include "audio.h"
#include "ledgerLine.h"
#include "barLine.h"
#include "staff.h"
#include "trebleClef.h"
#include "play.h"
#include "rest.h"

#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

static D3D11_BUFFER_DESC bd{};
static D3D11_SUBRESOURCE_DATA sd{};


void Player::Init()
{
	//頂点データ
	vertex[0] = { D3DXVECTOR3(position.x          , position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[0].x, tex[0].y) };
	vertex[1] = { D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[1].x, tex[1].y) };
	vertex[2] = { D3DXVECTOR3(position.x          , position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[2].x, tex[2].y) };
	vertex[3] = { D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[3].x, tex[3].y) };
	

	//音符テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile
	(//全音符
		Renderer::GetDevice(),
		"asset/texture/whole-note.png",
		NULL,
		NULL,
		&NoteTexture[whole],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//２分音符
		Renderer::GetDevice(),
		"asset/texture/half-note.png",
		NULL,
		NULL,
		&NoteTexture[half],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//４分音符
		Renderer::GetDevice(),
		"asset/texture/quarter-note.png",
		NULL,
		NULL,
		&NoteTexture[quarter],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//８分音符
		Renderer::GetDevice(),
		"asset/texture/eighth-note.png",
		NULL,
		NULL,
		&NoteTexture[eighth],
		NULL
	);

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


	assert(NoteTexture[whole]);		//エラーを処理するための仕組み
	assert(NoteTexture[half]);		
	assert(NoteTexture[quarter]);	
	assert(NoteTexture[eighth]);	
	assert(RestTexture[whole]);
	assert(RestTexture[half]);
	assert(RestTexture[quarter]);
	assert(RestTexture[eighth]);
	//デバッグ実行のときにテクスチャが読み込めたかをチェックしてくれる


	//レンダラークラスの中に作ってある関数を使ってる
	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Scene* scene = Manager::GetScene();

	_noteSE = scene->AddObject<Audio>(2);
	_noteSE->Load("asset\\sound\\se\\note.wav");

	noteSE[1] = scene->AddObject<Audio>(2);
	noteSE[1]->Load("asset\\sound\\se\\pianoC1.wav");

	noteSE[2] = scene->AddObject<Audio>(2);
	noteSE[2]->Load("asset\\sound\\se\\pianoH.wav");

	noteSE[3] = scene->AddObject<Audio>(2);
	noteSE[3]->Load("asset\\sound\\se\\pianoA.wav");

	noteSE[4] = scene->AddObject<Audio>(2);
	noteSE[4]->Load("asset\\sound\\se\\pianoG.wav");

	noteSE[5] = scene->AddObject<Audio>(2);
	noteSE[5]->Load("asset\\sound\\se\\pianoF.wav");

	noteSE[6] = scene->AddObject<Audio>(2);
	noteSE[6]->Load("asset\\sound\\se\\pianoE.wav");

	noteSE[7] = scene->AddObject<Audio>(2);
	noteSE[7]->Load("asset\\sound\\se\\pianoD.wav");

	noteSE[8] = scene->AddObject<Audio>(2);
	noteSE[8]->Load("asset\\sound\\se\\pianoC.wav");

	//初期位置
	startpos = { 100.0f,C,0.0f };
	position = startpos;
	scale = { 190.0f,190.0f,0.0f };
	rotation = { 0.0f,0.0f,0.0f };

	type = quarter;
	num = 0;
	notenum = 0;
	barnum = 0;
	system = 1;
	noteNum = 0;
	length = 10;
	cnt = 0;
	rest = false;
	ledgerline = false;

	tex[0] = { 0.0f, 0.0f };
	tex[1] = { 1.0f, 0.0f };
	tex[2] = { 0.0f, 1.0f };
	tex[3] = { 1.0f, 1.0f };
}

void Player::Uninit()
{
	VertexBuffer->Release();

	for (int i = 0; i < 3; i++)
	{
		NoteTexture[i]->Release();
	}

	for (int i = 0; i < 3; i++)
	{
		RestTexture[i]->Release();
	}

	VertexLayout->Release();
	VertexShader->Release();
	PixelShader->Release();
}

void Player::Update()
{
	Scene* scene = Manager::GetScene();
	std::vector<LedgerLine*>lineList = scene->GetObjects<LedgerLine>(1);//加線の情報を取得
	std::vector<BarLine*>BerLineList = scene->GetObjects<BarLine>(1);//小節線の情報を取得

	//音符の位置変更
	if (Input::GetKeyTrigger('W'))
	{
		position.y -= 11.5f;
	}
	if (Input::GetKeyTrigger('S'))
	{
		position.y += 11.5f;
	}

	//音符の種類変更
	if (Input::GetKeyTrigger(VK_UP))
	{
		type++;
		if (type > 3) type = 0;
	}
	if (Input::GetKeyTrigger(VK_DOWN))
	{
		type--;
		if (type < 0) type = 3;
	}

	if (Input::GetKeyTrigger(VK_RETURN))
	{//エンターキーを押したら
		//scene->AddObject<Play>(1)->Setnum(num);

		if (play)
		{
			play = false;
			noteNum = 0;
			cnt = 0;
		}

		if (!play)
		{//分けると再生途中でも最初から再生できる
			play = true;
		}
	}

	if (Input::GetKeyTrigger('C'))
	{//Cキーを押したら休符と音符の変更
		if (rest)
		{
			rest = false;
			position.y = startpos.y;
		}
		else
		{
			rest = true;
		}
	}

	if (rest)
	{
		position.y = 70.0f + (nextStaff * (system - 1));
	}

	//Y軸方向の限界調整
	if (position.y <= C1 + nextStaff * (system - 1))
	{//C1を越えないように
		position.y = C1 + nextStaff * (system - 1);
	}

	if (position.y >= C + nextStaff * (system - 1))
	{//Cを越えないように
		position.y = C + nextStaff * (system - 1);
		if (!ledgerline)
		{
			scene->AddObject<LedgerLine>(1)->SetPosition(position);//加線追加
			ledgerline = true;
		}
	}
	else
	{
		for (LedgerLine* line : lineList)
		{//加線を削除するかどうか
			D3DXVECTOR3 linePos = line->GetPosition();

			if (linePos.x == position.x && linePos.y != position.y)
			{
				line->SetDestroy();
				ledgerline = false;
				return;
			}
		}
	}

	//if (position.y = C + nextStaff * (system - 1))
	//{
	//	scene->AddObject<LedgerLine>(1)->SetPosition(position);//加線追加

	//}

	if (Input::GetKeyTrigger(VK_SPACE))
	{//スペースキーを押したら音符を決定
		//音符を配置してその音は何かを記録
		if (position.y == C)
		{
			scene->AddObject<LedgerLine>(1)->SetPosition(position);//加線追加
		}

		if (!rest)
		{
			scene->AddObject<Note>(1)->Set(type, position);//音符確定
		}
		else
		{
			scene->AddObject<Rest>(1)->Set(type, position);//音符確定
		}
		
		//どの音符か判断して対応した数字をjsonで記録
		//決定したときにその音を流す
		//２行目がまだできない
		if (position.y == C1 || position.y == (C1 + (system * nextStaff)))
		{
			note[num].name = "C1";
			note[num].y = C1;

			noteSE[1]->Play();
		}
		else if (position.y == H)
		{
			note[num].name = "H";
			note[num].y = H;

			noteSE[2]->Play();
		}
		else if (position.y == A)
		{
			note[num].name = "A";
			note[num].y = A;

			noteSE[3]->Play();
		}
		else if (position.y == G)
		{
			note[num].name = "G";
			note[num].y = G;

			noteSE[4]->Play();
		}
		else if (position.y == F)
		{
			note[num].name = "F";
			note[num].y = F;

			noteSE[5]->Play();
		}
		else if (position.y == E)
		{
			note[num].name = "E";
			note[num].y = E;

			noteSE[6]->Play();
		}
		else if (position.y == D)
		{
			note[num].name = "D";
			note[num].y = D;

			noteSE[7]->Play();
		}
		else if (position.y == C)
		{
			note[num].name = "C";
			note[num].y = C;

			noteSE[8]->Play();
		}
		
		if (rest)
		{
			note[num].name = "rest";
			note[num].y = 70.0f + (nextStaff * (system - 1));

			_noteSE->Play();
		}

		note[num].id = num;

		note[num].type = type;


		//どのくらい右に移動するか
		switch (type)
		{
		case whole:
			//numが8の倍数になったら小節線追加
			if (num == (8 * barnum))
			{//numが8の倍数になったら
				D3DXVECTOR3 pos = position;
				pos.x += 370.0f;
				pos.y = 97.0f + (nextStaff * (system - 1));
				scene->AddObject<BarLine>(1)->SetPosition(pos);//小節線追加
				position.x += 40.0f;
				barnum++;
			}
			
			position.x += 90 * 4;
			num += 8;
			notenum += 8;
			break;

		case half:
			//numが8の倍数になったら小節線追加
			if (num == (8 * barnum) + 4)
			{//numが8の倍数になったら
				D3DXVECTOR3 pos = position;
				pos.x += 200.0f;
				pos.y = 97.0f + (nextStaff * (system - 1));
				scene->AddObject<BarLine>(1)->SetPosition(pos);//小節線追加
				position.x += 30.0f;
				barnum++;
			}
			
			position.x += 90 * 2;
			num += 4;
			notenum += 4;
			break;

		case quarter:
			//numが8の倍数になったら小節線追加
			if (num == (8 * barnum) + 6)
			{//numが8の倍数になったら
				D3DXVECTOR3 pos = position;
				pos.x += 100.0f;
				pos.y = 97.0f + (nextStaff * (system - 1));
				scene->AddObject<BarLine>(1)->SetPosition(pos);//小節線追加
				position.x += 40.0f;
				barnum++;
			}

			position.x += 90;
			num += 2;
			notenum += 2;
			break;

		case eighth:
			//numが8の倍数になったら小節線追加
			if (num == (8 * barnum) + 7)
			{//numが8の倍数になったら
				D3DXVECTOR3 pos = position;
				pos.x += 80.0f;//小節線を右にずらして配置
				pos.y = 97.0f + (nextStaff * (system - 1));//小節線の高さ
				scene->AddObject<BarLine>(1)->SetPosition(pos);//小節線追加
				position.x += 30.0f;//小節線の分次の音符を右にずらす
				barnum++;
			}

			position.x += 90 / 2;
			num++;
			notenum++;
			break;

		default:
			break;
		}
	}

	if (!rest)
	{
		if (position.y <= H)
		{//シ以上の音だったら
			//符幹の向きを変更
			tex[0] = { 1.0f, 1.0f };
			tex[1] = { 0.0f, 1.0f };
			tex[2] = { 1.0f, 0.0f };
			tex[3] = { 0.0f, 0.0f };
		}
		else
		{//ラ以下の音だったら
			//符幹の向きをもとに戻す
			tex[0] = { 0.0f, 0.0f };
			tex[1] = { 1.0f, 0.0f };
			tex[2] = { 0.0f, 1.0f };
			tex[3] = { 1.0f, 1.0f };
		}
	}

	if (barnum == (system * 2))
	{//2段目になったら
		scene->AddObject<Staff>(1)->NewLine(system);//五線譜追加
		scene->AddObject<TrebleClef>(1)->NextTrebleClef(system);//ト音記号追加
		system++;
		position.y += nextStaff;
		position.x = startpos.x;//左に戻す
	}

	//ファイル出力
	std::ofstream os("notes.json", std::ios::out);//jsonのファイルに出力
	cereal::JSONOutputArchive archiveFile(os);
	{
		archiveFile(cereal::make_nvp("notes", note));
	}


	//読み込んだ順に音を鳴らす
	if (!play)return;

	////jsonファイル読み込み
	//std::ifstream os("notes.json", std::ios::in);
	//cereal::JSONInputArchive archive(os);

	//noteLoad[num].serialize(archive);

	cnt++;

	if (cnt == length)
	{
		if (note[noteNum].name == "C1")
		{//音符の種類によって鳴らす音を変える
			noteSE[1]->Play();
		}
		else if (note[noteNum].name == "H")
		{
			noteSE[2]->Play();
		}
		else if (note[noteNum].name == "A")
		{
			noteSE[3]->Play();
		}
		else if (note[noteNum].name == "G")
		{
			noteSE[4]->Play();
		}
		else if (note[noteNum].name == "F")
		{
			noteSE[5]->Play();
		}
		else if (note[noteNum].name == "E")
		{
			noteSE[6]->Play();
		}
		else if (note[noteNum].name == "D")
		{
			noteSE[7]->Play();
		}
		else if(note[noteNum].name == "C")
		{
			noteSE[8]->Play();
		}

		cnt = 0;
		noteNum++;
	}

}

void Player::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//頂点データ
	vertex[0] = { D3DXVECTOR3(position.x          , position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[0].x, tex[0].y) };
	vertex[1] = { D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[1].x, tex[1].y) };
	vertex[2] = { D3DXVECTOR3(position.x          , position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[2].x, tex[2].y) };
	vertex[3] = { D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[3].x, tex[3].y) };

	//頂点バッファ生成
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	//テクスチャ設定
	if (!rest)
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &NoteTexture[type]);
	}
	else
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &RestTexture[type]);
	}

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

