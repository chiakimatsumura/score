#pragma once

#include "object.h"

class Rest : public Object
{
private:
	//NULL�`�F�b�N����Ȃ�����
	//NULL�����Ȃ�S���ɓ���ē��ꂷ��
	ID3D11Buffer*				VertexBuffer = NULL;
	ID3D11ShaderResourceView*	RestTexture[4] = { NULL };
	ID3D11ShaderResourceView*	Texture = NULL;

	ID3D11VertexShader*		VertexShader = NULL;
	ID3D11PixelShader*		PixelShader = NULL;
	ID3D11InputLayout*		VertexLayout = NULL;

	VERTEX_3D restVertex[4];

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(int type, D3DXVECTOR3 pos);


};