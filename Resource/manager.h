#pragma once


class Manager
{//マネージャークラス

private:
	static class Scene* scene;//メンバ変数もスタティックじゃないとだめ
	//classをつけるとインクルードしなくても大丈夫
	//staticにすると実態はつくられないからcppでもう一回宣言しないといけない

	static class Input* input;

public:
	//メソッド、メンバ関数
	static void Init();		//初期化
	static void Uninit();	//終了
	static void Update();	//更新
	static void Draw();		//描画

	static class Scene* GetScene() { return scene; }

	template<typename T>
	static void SetScene()
	{//画面を切り替える
		if (scene)
		{
			scene->Uninit();
			delete scene;
		}

		T* newScene = new T();
		scene = newScene;
		newScene->Init();
	}

};