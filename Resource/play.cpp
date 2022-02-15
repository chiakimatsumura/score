//#include "main.h"
//#include "manager.h"
//#include "renderer.h"
//
//#include "play.h"
//#include "scene.h"
//#include "audio.h"
//
//#include <fstream>
//#include <cereal/archives/json.hpp>
//
//void Play::Init()
//{
//	Scene* scene = Manager::GetScene();
//
//	noteSE_1 = scene->AddObject<Audio>(2);
//	noteSE_1->Load("asset\\sound\\se\\pianoC1.wav");
//
//	noteSE_2 = scene->AddObject<Audio>(2);
//	noteSE_2->Load("asset\\sound\\se\\pianoH.wav");
//
//	noteSE_3 = scene->AddObject<Audio>(2);
//	noteSE_3->Load("asset\\sound\\se\\pianoA.wav");
//
//	noteSE_4 = scene->AddObject<Audio>(2);
//	noteSE_4->Load("asset\\sound\\se\\pianoG.wav");
//
//	noteSE_5 = scene->AddObject<Audio>(2);
//	noteSE_5->Load("asset\\sound\\se\\pianoF.wav");
//
//	noteSE_6 = scene->AddObject<Audio>(2);
//	noteSE_6->Load("asset\\sound\\se\\pianoE.wav");
//
//	noteSE_7 = scene->AddObject<Audio>(2);
//	noteSE_7->Load("asset\\sound\\se\\pianoD.wav");
//
//	noteSE_8 = scene->AddObject<Audio>(2);
//	noteSE_8->Load("asset\\sound\\se\\pianoC.wav");
//
//	cnt = 0;//カウント
//
//	//jsonファイル読み込み
//	std::ifstream os("notes.json", std::ios::in);
//	cereal::JSONInputArchive archive(os);
//
//	noteLoad[num].serialize(archive);
//
//	for (int i = 0; i < num; i++)
//	{
//		notes[i] = noteLoad[i].y;
//	}
//
//
//}
//
//void Play::Uninit()
//{
//}
//
//void Play::Update()
//{
//	//読み込んだ順に音を鳴らす
//	cnt++;
//	static int noteNum = 1;
//	if (cnt == 100)
//	{
//		switch ((int)notes[noteNum])
//		{//音を鳴らす
//		case 66://C1
//			noteSE_1->Play();
//			break;
//
//		case 77://H
//			noteSE_2->Play();
//			break;
//
//		case 88://A
//			noteSE_3->Play();
//			break;
//
//		case 99://G
//			noteSE_4->Play();
//			break;
//
//		case 110://F
//			noteSE_5->Play();
//			break;
//
//		case 121://E
//			noteSE_6->Play();
//			break;
//
//		case 132://D
//			noteSE_7->Play();
//			break;
//
//		case 143://C
//			noteSE_8->Play();
//			break;
//
//		default:
//			break;
//		}
//		cnt = 0;
//		noteNum++;
//	}
//
//}
//
//void Play::Draw()
//{
//}
//
//void Play::Setnum(int n)
//{
//	num = n;
//}