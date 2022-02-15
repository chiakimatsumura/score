#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "titleLogo.h"

#include "title.h"

#include "work.h"

void Title::Init()
{
	//AddObject<�^����>(���C���[�̐���);
	AddObject<TitleLogo>(2);
}

void Title::Uninit()
{
	Scene::Uninit();//�p�����N���X�̃��\�b�h�Ăяo��
}

void Title::Update()
{
	Scene::Update();//�p�����N���X�̃��\�b�h�Ăяo��

	if (Input::GetKeyTrigger(VK_RETURN))
	{//�G���^�[�L�[�������ꂽ���ʑJ��
		Manager::SetScene<Work>();
	}
}
