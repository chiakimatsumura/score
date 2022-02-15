#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "titleLogo.h"

#include "title.h"

#include "work.h"

void Title::Init()
{
	//AddObject<型引数>(レイヤーの数字);
	AddObject<TitleLogo>(2);
}

void Title::Uninit()
{
	Scene::Uninit();//継承元クラスのメソッド呼び出し
}

void Title::Update()
{
	Scene::Update();//継承元クラスのメソッド呼び出し

	if (Input::GetKeyTrigger(VK_RETURN))
	{//エンターキーが押されたら画面遷移
		Manager::SetScene<Work>();
	}
}
