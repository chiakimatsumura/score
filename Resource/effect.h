//#pragma once
//
//#include "object.h"
//
//class Effect : public Object
//{
//private:
//	//NULLチェックいるなら入れる
//	//NULLいれるなら全部に入れて統一する
//	ID3D11Buffer*				VertexBuffer = NULL;
//	ID3D11ShaderResourceView*	Texture = NULL;
//
//	ID3D11VertexShader*		VertexShader = NULL;
//	ID3D11PixelShader*		PixelShader = NULL;
//	ID3D11InputLayout*		VertexLayout = NULL;
//
//	int count;
//
//public:
//	void Init();
//	void Uninit();
//	void Update();
//	void Draw();
//};