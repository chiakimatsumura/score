#pragma once

#include <list>//���X�g�\�����g���̂ɕK�v
#include <vector>//vector���g���̂ɕK�v
#include <typeinfo>//typeid���g���̂ɕK�v
#include "object.h"

#define		LAYER	(3)//���C���[�̐�

class Scene//���z�N���X ���z�N���X�̓C���X�^���X�̐������ł��Ȃ�
{//�p����p�̃N���X
protected:
	std::list<Object*>	object[LAYER];//STL(�X�^���_�[�h�e���v���[�g���C�u�����[)�̃��X�g�\��

public:
	Scene() {}
	virtual ~Scene() {}//�f�X�g���N�^�͉��z�֐�

	virtual void Init() = 0;//�|�����[�t�B�Y���Ōp����̊֐��ɌĂ΂������Ƃ���virtual������
	//�������z�֐��ɂ����Scene�N���X�̃C���X�^���X�������ł��Ȃ��Ȃ�


	template <typename T> //�e���v���[�g�֐�
	T* AddObject(int layer)
	{
		T* obj = new T();
		object[layer].push_back(obj);//��Ƀ��X�g�ɓo�^���Ă���Init���ĂԂ�Init�̒��ő��̃I�u�W�F�N�g�̐��l���g����悤�ɂȂ�
		obj->Init();

		return obj;
	}

	template<typename T>
	T* GetObj(int layer)
	{
		for (Object* object : object[layer])
		{
			if (typeid(*object) == typeid(T))//�^�𒲂ׂ�Btypeid�Ō^�𒲂ׂ���(RTTI���I�^���)
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	template<typename T>
	std::vector<T*> GetObjects(int layer)
	{
		std::vector<T*> objects;//STL�̔z��
		for (Object* object : object[layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	virtual void Uninit()
	{
		for (int i = 0; i < LAYER; i++)
		{

			for (Object* object : object[i])//�o�^����Ă�I�u�W�F�N�g�̂��ׂĂ�uninit�����Ă����
			{
				object->Uninit();
				delete object;
			}
			object[i].clear();//���X�g�̃N���A
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < LAYER; i++)
		{

			for (Object* object : object[i])
			{
				object->Update();
			}

			object[i].remove_if([](Object* object) {return object->Destroy(); });//�����_��
			//()�̒��������B�����_����[]�Ƃ������O�̂Ȃ��֐�������Ă銴���B���ʂ̊֐��͓�����Ȃ�
			//�����\��̃t���O�𒲂ׂĂ��ׂẴQ�[���I�u�W�F�N�g����true���������������
		}
	}

	virtual void Draw()
	{
		//�|���S����`�悷��Ƃ��͂����ɏ���
		//���ԑ厖�I
		//�J�����A3D�|���S���AUI�̏���
		for (int i = 0; i < LAYER; i++)
		{
			for (Object* object : object[i])
			{
				object->Draw();
			}
		}
	}
};