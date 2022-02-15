#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "audio.h"
#include "scene.h"
#include "title.h"
#include "work.h"
#include "result.h"

Scene* Manager::scene = NULL;//NULLチェックが入ってるから初期値にNULLをいれる
Input* Manager::input;

//クラス名::メンバ関数、メソッド名
void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();

	SetScene<Title>();
}


void Manager::Uninit()
{
	scene->Uninit();
	delete scene;

	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	scene->Update();
	Input::Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	scene->Draw();

	Renderer::End();
}
