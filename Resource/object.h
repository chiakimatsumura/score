#pragma once

class Object//���z�N���X ���̃N���X�����ł͎g��Ȃ����牼�z�N���X
{//�e�N���X�ɋ��ʂ̋@�\�����̃N���X�ɂ܂Ƃ߂�
protected://�p����̃N���X����A�N�Z�X�ł���

	bool		destroy = false;//�����\������邽�߂̃t���O

	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 velocity;
	D3DXVECTOR2 tex[4];

public:
	Object() {}//�R���X�g���N�^ �C���X�^���X���������ꂽ�Ƃ��Ɏ����I�ɌĂяo�����֐�
	virtual ~Object() {}//�f�X�g���N�^(���z�֐�)
	//virtual�����Ȃ��ƁAObject�̃f�X�g���N�^���Ă΂�Ă��܂��āA�p����̃f�X�g���N�^���Ăяo����Ȃ��������
	//�R���X�g���N�^�ɂ�virtual�������Ȃ� �R���p�C���G���[�ɂȂ�

	//Object�ɂ͑��݂��Ȃ����ǁA�p����̃N���X�ł͑��݂���\�肾�Ɛ錾����
	//=0�͂��̂��炷�ɂ͑��݂��Ȃ��Ƃ����Ӗ�
	virtual void Init() = 0;	//�������z�֐�
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	D3DXVECTOR3 GetPosition() { return position; }
	void SetPosition(D3DXVECTOR3 pos) { position = pos; }
	void SetRotation(D3DXVECTOR3 rot) { rotation = rot; }
	void SetScale(D3DXVECTOR3 sca) { scale = sca; }
	void SetVelocity(D3DXVECTOR3 vel) { velocity = vel; }

	D3DXVECTOR3 GetForward()//�O�����x�N�g���擾
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, rotation.y, rotation.x, rotation.z);

		D3DXVECTOR3 forward;//�O������\���x�N�g��
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()//�E�����x�N�g���擾
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, rotation.y, rotation.x, rotation.z);

		D3DXVECTOR3 Right;//�E������\���x�N�g��
		Right.x = rot._11;
		Right.y = rot._12;
		Right.z = rot._13;

		return Right;
	}

	D3DXVECTOR3 GetUp()//������x�N�g���擾
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, rotation.y, rotation.x, rotation.z);

		D3DXVECTOR3 Up;//�������\���x�N�g��
		Up.x = rot._21;
		Up.y = rot._22;
		Up.z = rot._23;

		return Up;
	}


	void SetDestroy() { destroy = true; }//destroy���O������ݒ肷��d�g��

	bool Destroy()
	{
		if (destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	 float C1 = 62.5f;
	 float H = 74.0f;
	 float A = 85.5f;
	 float G = 97.0f;
	 float F = 108.5f;
	 float E = 120.0f;
	 float D = 131.5f;
	 float C = 143.0f;

	 float nextStaff = 220.0f;

	 const static enum
	 {
		 whole = 0,
		 half,
		 quarter,
		 eighth,
		 sixteenth,
	 }TYPE;

	 const enum
	 {
		 C_NOTE = 0,
		 D_NOTE,
		 E_NOTE,
		 F_NOTE,
		 G_NOTE,
		 A_NOTE,
		 H_NOTE,
		 C1_NOTE,
	 };
};