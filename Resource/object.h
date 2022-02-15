#pragma once

class Object//仮想クラス このクラスだけでは使わないから仮想クラス
{//各クラスに共通の機能をこのクラスにまとめる
protected://継承先のクラスからアクセスできる

	bool		destroy = false;//消す予約をするためのフラグ

	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 velocity;
	D3DXVECTOR2 tex[4];

public:
	Object() {}//コンストラクタ インスタンスが生成されたときに自動的に呼び出される関数
	virtual ~Object() {}//デストラクタ(仮想関数)
	//virtualをつけないと、Objectのデストラクタが呼ばれてしまって、継承先のデストラクタが呼び出されないからつける
	//コンストラクタにはvirtualをつけられない コンパイルエラーになる

	//Objectには存在しないけど、継承先のクラスでは存在する予定だと宣言する
	//=0はこのくらすには存在しないという意味
	virtual void Init() = 0;	//純粋仮想関数
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	D3DXVECTOR3 GetPosition() { return position; }
	void SetPosition(D3DXVECTOR3 pos) { position = pos; }
	void SetRotation(D3DXVECTOR3 rot) { rotation = rot; }
	void SetScale(D3DXVECTOR3 sca) { scale = sca; }
	void SetVelocity(D3DXVECTOR3 vel) { velocity = vel; }

	D3DXVECTOR3 GetForward()//前方向ベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, rotation.y, rotation.x, rotation.z);

		D3DXVECTOR3 forward;//前方向を表すベクトル
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()//右方向ベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, rotation.y, rotation.x, rotation.z);

		D3DXVECTOR3 Right;//右方向を表すベクトル
		Right.x = rot._11;
		Right.y = rot._12;
		Right.z = rot._13;

		return Right;
	}

	D3DXVECTOR3 GetUp()//上方向ベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, rotation.y, rotation.x, rotation.z);

		D3DXVECTOR3 Up;//上方向を表すベクトル
		Up.x = rot._21;
		Up.y = rot._22;
		Up.z = rot._23;

		return Up;
	}


	void SetDestroy() { destroy = true; }//destroyを外部から設定する仕組み

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