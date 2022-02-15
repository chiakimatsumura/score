
#include "main.h"
#include "manager.h"
#include "note.h"
#include "noteSpawner.h"
#include "scene.h"

void NoteSpawner::Init()                      
{

	frame = 0;
	index = 0;
	//position = { SCREEN_WIDTH,0.0f,0.0f };
}

void NoteSpawner::Uninit()
{
}

void NoteSpawner::Update()
{
	//while (g_data[index] <= frame)
	//{
	//	if (g_data[index] < 0)
	//	{
	//		break;
	//	}
	//	static int noteRand;
	//	noteRand = rand() % 6 + 0;		//0-1のランダムな値を取得(音符ランダム用)
	//	if (noteRand > 1)
	//	{
	//		//position.y = 265.0f;
	//		position = { SCREEN_WIDTH,265.0f,0.0f };
	//	}
	//	else
	//	{
	//		//position.y = 0.0f;
	//		position = { SCREEN_WIDTH,0.0f,0.0f };
	//	}





}

void NoteSpawner::Draw()
{
}

void NoteSpawner::set(D3DXVECTOR3 pos, int type)
{
	//if(pos=)


	Scene* scene = Manager::GetScene();
	scene->AddObject<Note>(1)->Set(type, pos), SetPosition(position);

}
