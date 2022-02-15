#pragma once

#include "object.h"

class NoteSpawner : public Object
{
private:
	int frame;
	int index;

public:

	//struct Spawn
	//{
	//	int frame;
	//	float x, y;
	//	//NoteType type;
	//};

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void set(D3DXVECTOR3 pos, int type);
};