//この3つはほとんどのcppで必要
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//インスタンス生成しなきゃいけないクラスのヘッダー
#include "camera.h"
#include "polygon2D.h"
#include "audio.h"
#include "background.h"
#include "noteSpawner.h"
#include "player.h"
#include "staff.h"
#include "trebleClef.h"
#include "timeSignature.h"

//自分のクラスのヘッダー
#include "work.h"

//遷移先のヘッダー
#include "result.h"
#include "title.h"

void Work::Init()
{
	//AddObject<型引数>(普通の関数の引数);
	AddObject<Camera>(0);

	//AddObject<Background>(0);
	AddObject<Staff>(1);
	AddObject<TrebleClef>(1);
	AddObject<TimeSignature>(1);

	AddObject<Player>(1);


	AddObject<NoteSpawner>(2);


	//Audio *bgm = AddObject<Audio>(2);//()の中は関係ない
	//bgm->Load("asset\\sound\\bgm\\Cat_life.wav");
	//bgm->Play(true);//サウンド再生


}

void Work::Uninit()
{
	Scene::Uninit();//継承元クラスのメソッド呼び出し
	//メソッドがオーバーライドされていると、呼び出されるのは一つのメソッドだから、sceneのUninit()は呼ばれなくなる
	//でもworkの中でUninitが必要だからここで書いてる
}

void Work::Update()
{
	Scene::Update();//継承元クラスのメソッド呼び出し

	if (Input::GetKeyTrigger(VK_DELETE))
	{//デリートキーが押されたらリセットする
		Manager::SetScene<Work>();
	}

	//if (frame == 4225)
	//{//リザルトへ
	//	Manager::SetScene<Result>();
	//}
	//frame++;

}
