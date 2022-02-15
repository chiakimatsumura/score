#pragma once

#include "object.h"
#include <cereal/types/string.hpp>

class Player : public Object
{
private:
	//NULLチェックいるなら入れる
	//NULLいれるなら全部に入れて統一する
	ID3D11Buffer*				VertexBuffer = NULL;
	ID3D11ShaderResourceView*	NoteTexture[4] = {NULL};
	ID3D11ShaderResourceView*	RestTexture[4] = {NULL};

	ID3D11VertexShader*		VertexShader = NULL;
	ID3D11PixelShader*		PixelShader = NULL;
	ID3D11InputLayout*		VertexLayout = NULL;

	class Audio* _noteSE;

	class Audio* noteSE[9];

	int type;//音符の種類
	int barnum;//小節線の数
	int system;//段数
	int cnt;//音と音の間隔

	bool play = false;//再生してるか

	int noteNum;//音再生のときの順番用
	int num;//音符の配列用
	int notenum;//音符の数計算用
	int length;//音符の長さ用
	D3DXVECTOR3 startpos;//初期位置設定用
	bool rest;//休符かどうかの状態
	bool ledgerline;//加線があるかどうか

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

	Notes note[32];//json用
	Notes noteLoad[32];

};