#pragma once

#include "object.h"

class Camera : public Object
{
private:
	D3DXVECTOR3 target;
	D3DXMATRIX ViewMatrix;

	ID3D11VertexShader*		VertexShader = NULL;
	ID3D11PixelShader*		PixelShader = NULL;
	ID3D11InputLayout*		VertexLayout = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return ViewMatrix; }
};