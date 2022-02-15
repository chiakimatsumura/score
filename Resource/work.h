#pragma once

#include "scene.h"

class Work : public Scene
{
private:
	int frame;
public:
	void Init();
	void Uninit();
	void Update();
};