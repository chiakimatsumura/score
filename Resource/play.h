//#pragma once
//#include "object.h"
//#include "player.h"
//
//class Play : public Object
//{
//private:
//	//NULL�`�F�b�N����Ȃ�����
//	//NULL�����Ȃ�S���ɓ���ē��ꂷ��
//	ID3D11Buffer*				VertexBuffer = NULL;
//	ID3D11ShaderResourceView*	QuarterNoteTexture = NULL;
//
//	ID3D11VertexShader*		VertexShader = NULL;
//	ID3D11PixelShader*		PixelShader = NULL;
//	ID3D11InputLayout*		VertexLayout = NULL;
//
//	class Audio* noteSE_1;
//	class Audio* noteSE_2;
//	class Audio* noteSE_3;
//	class Audio* noteSE_4;
//	class Audio* noteSE_5;
//	class Audio* noteSE_6;
//	class Audio* noteSE_7;
//	class Audio* noteSE_8;
//	int num;
//	int cnt;
//	int notes[30];
//
//public:
//
//	void Init();
//	void Uninit();
//	void Update();
//	void Draw();
//
//	void Setnum(int n);
//
//
//	Player::Notes noteLoad[30];
//
//};