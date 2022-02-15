//#include "main.h"
//#include "manager.h"
//#include "renderer.h"
//#include "input.h"
//
//#include "resultLogo.h"
//
//#include "result.h"
//
////遷移先のヘッダー
//#include "title.h"
//
//void Result::Init()
//{
//	//AddObject<型引数>(レイヤーの数字);
//	AddObject<ResultLogo>(2);
//}
//
//void Result::Uninit()
//{
//	Scene::Uninit();//継承元クラスのメソッド呼び出し
//}
//
//void Result::Update()
//{
//	Scene::Update();//継承元クラスのメソッド呼び出し
//
//	//ここでタイトルへ画面遷移する処理
//	if (Input::GetKeyTrigger(VK_RETURN))
//	{//エンターキーが押されたら画面遷移
//		Manager::SetScene<Title>();
//	}
//}
