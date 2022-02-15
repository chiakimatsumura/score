#pragma once


class Manager
{//�}�l�[�W���[�N���X

private:
	static class Scene* scene;//�����o�ϐ����X�^�e�B�b�N����Ȃ��Ƃ���
	//class������ƃC���N���[�h���Ȃ��Ă����v
	//static�ɂ���Ǝ��Ԃ͂����Ȃ�����cpp�ł������錾���Ȃ��Ƃ����Ȃ�

	static class Input* input;

public:
	//���\�b�h�A�����o�֐�
	static void Init();		//������
	static void Uninit();	//�I��
	static void Update();	//�X�V
	static void Draw();		//�`��

	static class Scene* GetScene() { return scene; }

	template<typename T>
	static void SetScene()
	{//��ʂ�؂�ւ���
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