#pragma once

#include "object.h"

class TimeSignature : public Object
{
private:
	//NULL�`�F�b�N����Ȃ�����
	//NULL�����Ȃ�S���ɓ���ē��ꂷ��
	ID3D11Buffer*				VertexBuffer = NULL;
	ID3D11ShaderResourceView*	Texture = NULL;

	ID3D11VertexShader*		VertexShader = NULL;
	ID3D11PixelShader*		PixelShader = NULL;
	ID3D11InputLayout*		VertexLayout = NULL;

	class Audio* _noteSE;

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

};