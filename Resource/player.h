#pragma once

#include "object.h"
#include <cereal/types/string.hpp>

class Player : public Object
{
private:
	//NULL�`�F�b�N����Ȃ�����
	//NULL�����Ȃ�S���ɓ���ē��ꂷ��
	ID3D11Buffer*				VertexBuffer = NULL;
	ID3D11ShaderResourceView*	NoteTexture[4] = {NULL};
	ID3D11ShaderResourceView*	RestTexture[4] = {NULL};

	ID3D11VertexShader*		VertexShader = NULL;
	ID3D11PixelShader*		PixelShader = NULL;
	ID3D11InputLayout*		VertexLayout = NULL;

	class Audio* _noteSE;

	class Audio* noteSE[9];

	int type;//�����̎��
	int barnum;//���ߐ��̐�
	int system;//�i��
	int cnt;//���Ɖ��̊Ԋu

	bool play = false;//�Đ����Ă邩

	int noteNum;//���Đ��̂Ƃ��̏��ԗp
	int num;//�����̔z��p
	int notenum;//�����̐��v�Z�p
	int length;//�����̒����p
	D3DXVECTOR3 startpos;//�����ʒu�ݒ�p
	bool rest;//�x�����ǂ����̏��
	bool ledgerline;//���������邩�ǂ���

	VERTEX_3D vertex[4];


public:

	void Init();
	void Uninit();
	void Update();
	void Draw();


	struct Notes
	{
		int id;
		std::string name;
		int type;
		float y = 0;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(CEREAL_NVP(id), CEREAL_NVP(name), CEREAL_NVP(type), CEREAL_NVP(y));
		}
	};

	Notes note[32];//json�p
	Notes noteLoad[32];

};