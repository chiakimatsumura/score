#pragma once

#include "object.h"

class TitleLogo : public Object
{
private:
	//NULLチェックいるなら入れる
	//NULLいれるなら全部に入れて統一する
	ID3D11Buffer*				VertexBuffer = NULL;
	ID3D11ShaderResourceView*	Texture = NULL;

	ID3D11VertexShader*		VertexShader = NULL;
	ID3D11PixelShader*		PixelShader = NULL;
	ID3D11InputLayout*		VertexLayout = NULL;

public:
	//TitleLogo();	//コンストラクタ
	//~TitleLogo();	//デストラクタ
	//使わないときは入れなくても大丈夫

	void Init();
	void Uninit();
	void Update();
	void Draw();
};