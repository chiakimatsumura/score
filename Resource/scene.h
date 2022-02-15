#pragma once

#include <list>//リスト構造を使うのに必要
#include <vector>//vectorを使うのに必要
#include <typeinfo>//typeidを使うのに必要
#include "object.h"

#define		LAYER	(3)//レイヤーの数

class Scene//仮想クラス 仮想クラスはインスタンスの生成ができない
{//継承専用のクラス
protected:
	std::list<Object*>	object[LAYER];//STL(スタンダードテンプレートライブラリー)のリスト構造

public:
	Scene() {}
	virtual ~Scene() {}//デストラクタは仮想関数

	virtual void Init() = 0;//ポリモーフィズムで継承先の関数に呼ばせたいときはvirtualをつける
	//純粋仮想関数にするとSceneクラスのインスタンスが生成できなくなる


	template <typename T> //テンプレート関数
	T* AddObject(int layer)
	{
		T* obj = new T();
		object[layer].push_back(obj);//先にリストに登録してからInitを呼ぶとInitの中で他のオブジェクトの数値が使えるようになる
		obj->Init();

		return obj;
	}

	template<typename T>
	T* GetObj(int layer)
	{
		for (Object* object : object[layer])
		{
			if (typeid(*object) == typeid(T))//型を調べる。typeidで型を調べられる(RTTI動的型情報)
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	template<typename T>
	std::vector<T*> GetObjects(int layer)
	{
		std::vector<T*> objects;//STLの配列
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

			for (Object* object : object[i])//登録されてるオブジェクトのすべてのuninitをしてくれる
			{
				object->Uninit();
				delete object;
			}
			object[i].clear();//リストのクリア
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

			object[i].remove_if([](Object* object) {return object->Destroy(); });//ラムダ式
			//()の中が条件。ラムダ式で[]という名前のない関数を作ってる感じ。普通の関数は入れられない
			//消す予約のフラグを調べてすべてのゲームオブジェクトからtrueが見つかったら消す
		}
	}

	virtual void Draw()
	{
		//ポリゴンを描画するときはここに書く
		//順番大事！
		//カメラ、3Dポリゴン、UIの順番
		for (int i = 0; i < LAYER; i++)
		{
			for (Object* object : object[i])
			{
				object->Draw();
			}
		}
	}
};