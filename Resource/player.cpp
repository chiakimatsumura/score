
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "player.h"
#include "input.h"
#include "scene.h"
#include "note.h"
#include "effect.h"
#include "audio.h"
#include "ledgerLine.h"
#include "barLine.h"
#include "staff.h"
#include "trebleClef.h"
#include "play.h"
#include "rest.h"

#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

static D3D11_BUFFER_DESC bd{};
static D3D11_SUBRESOURCE_DATA sd{};


void Player::Init()
{
	//���_�f�[�^
	vertex[0] = { D3DXVECTOR3(position.x          , position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[0].x, tex[0].y) };
	vertex[1] = { D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[1].x, tex[1].y) };
	vertex[2] = { D3DXVECTOR3(position.x          , position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[2].x, tex[2].y) };
	vertex[3] = { D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[3].x, tex[3].y) };
	

	//�����e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(//�S����
		Renderer::GetDevice(),
		"asset/texture/whole-note.png",
		NULL,
		NULL,
		&NoteTexture[whole],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//�Q������
		Renderer::GetDevice(),
		"asset/texture/half-note.png",
		NULL,
		NULL,
		&NoteTexture[half],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//�S������
		Renderer::GetDevice(),
		"asset/texture/quarter-note.png",
		NULL,
		NULL,
		&NoteTexture[quarter],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//�W������
		Renderer::GetDevice(),
		"asset/texture/eighth-note.png",
		NULL,
		NULL,
		&NoteTexture[eighth],
		NULL
	);

	//�x���e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(//�S�x��
		Renderer::GetDevice(),
		"asset/texture/whole-rest.png",
		NULL,
		NULL,
		&RestTexture[whole],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//�Q���x��
		Renderer::GetDevice(),
		"asset/texture/half-rest.png",
		NULL,
		NULL,
		&RestTexture[half],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//�S���x��
		Renderer::GetDevice(),
		"asset/texture/quarter-rest.png",
		NULL,
		NULL,
		&RestTexture[quarter],
		NULL
	);

	D3DX11CreateShaderResourceViewFromFile
	(//�W���x��
		Renderer::GetDevice(),
		"asset/texture/eighth-rest.png",
		NULL,
		NULL,
		&RestTexture[eighth],
		NULL
	);


	assert(NoteTexture[whole]);		//�G���[���������邽�߂̎d�g��
	assert(NoteTexture[half]);		
	assert(NoteTexture[quarter]);	
	assert(NoteTexture[eighth]);	
	assert(RestTexture[whole]);
	assert(RestTexture[half]);
	assert(RestTexture[quarter]);
	assert(RestTexture[eighth]);
	//�f�o�b�O���s�̂Ƃ��Ƀe�N�X�`�����ǂݍ��߂������`�F�b�N���Ă����


	//�����_���[�N���X�̒��ɍ���Ă���֐����g���Ă�
	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Scene* scene = Manager::GetScene();

	_noteSE = scene->AddObject<Audio>(2);
	_noteSE->Load("asset\\sound\\se\\note.wav");

	noteSE[1] = scene->AddObject<Audio>(2);
	noteSE[1]->Load("asset\\sound\\se\\pianoC1.wav");

	noteSE[2] = scene->AddObject<Audio>(2);
	noteSE[2]->Load("asset\\sound\\se\\pianoH.wav");

	noteSE[3] = scene->AddObject<Audio>(2);
	noteSE[3]->Load("asset\\sound\\se\\pianoA.wav");

	noteSE[4] = scene->AddObject<Audio>(2);
	noteSE[4]->Load("asset\\sound\\se\\pianoG.wav");

	noteSE[5] = scene->AddObject<Audio>(2);
	noteSE[5]->Load("asset\\sound\\se\\pianoF.wav");

	noteSE[6] = scene->AddObject<Audio>(2);
	noteSE[6]->Load("asset\\sound\\se\\pianoE.wav");

	noteSE[7] = scene->AddObject<Audio>(2);
	noteSE[7]->Load("asset\\sound\\se\\pianoD.wav");

	noteSE[8] = scene->AddObject<Audio>(2);
	noteSE[8]->Load("asset\\sound\\se\\pianoC.wav");

	//�����ʒu
	startpos = { 100.0f,C,0.0f };
	position = startpos;
	scale = { 190.0f,190.0f,0.0f };
	rotation = { 0.0f,0.0f,0.0f };

	type = quarter;
	num = 0;
	notenum = 0;
	barnum = 0;
	system = 1;
	noteNum = 0;
	length = 10;
	cnt = 0;
	rest = false;
	ledgerline = false;

	tex[0] = { 0.0f, 0.0f };
	tex[1] = { 1.0f, 0.0f };
	tex[2] = { 0.0f, 1.0f };
	tex[3] = { 1.0f, 1.0f };
}

void Player::Uninit()
{
	VertexBuffer->Release();

	for (int i = 0; i < 3; i++)
	{
		NoteTexture[i]->Release();
	}

	for (int i = 0; i < 3; i++)
	{
		RestTexture[i]->Release();
	}

	VertexLayout->Release();
	VertexShader->Release();
	PixelShader->Release();
}

void Player::Update()
{
	Scene* scene = Manager::GetScene();
	std::vector<LedgerLine*>lineList = scene->GetObjects<LedgerLine>(1);//�����̏����擾
	std::vector<BarLine*>BerLineList = scene->GetObjects<BarLine>(1);//���ߐ��̏����擾

	//�����̈ʒu�ύX
	if (Input::GetKeyTrigger('W'))
	{
		position.y -= 11.5f;
	}
	if (Input::GetKeyTrigger('S'))
	{
		position.y += 11.5f;
	}

	//�����̎�ޕύX
	if (Input::GetKeyTrigger(VK_UP))
	{
		type++;
		if (type > 3) type = 0;
	}
	if (Input::GetKeyTrigger(VK_DOWN))
	{
		type--;
		if (type < 0) type = 3;
	}

	if (Input::GetKeyTrigger(VK_RETURN))
	{//�G���^�[�L�[����������
		//scene->AddObject<Play>(1)->Setnum(num);

		if (play)
		{
			play = false;
			noteNum = 0;
			cnt = 0;
		}

		if (!play)
		{//������ƍĐ��r���ł��ŏ�����Đ��ł���
			play = true;
		}
	}

	if (Input::GetKeyTrigger('C'))
	{//C�L�[����������x���Ɖ����̕ύX
		if (rest)
		{
			rest = false;
			position.y = startpos.y;
		}
		else
		{
			rest = true;
		}
	}

	if (rest)
	{
		position.y = 70.0f + (nextStaff * (system - 1));
	}

	//Y�������̌��E����
	if (position.y <= C1 + nextStaff * (system - 1))
	{//C1���z���Ȃ��悤��
		position.y = C1 + nextStaff * (system - 1);
	}

	if (position.y >= C + nextStaff * (system - 1))
	{//C���z���Ȃ��悤��
		position.y = C + nextStaff * (system - 1);
		if (!ledgerline)
		{
			scene->AddObject<LedgerLine>(1)->SetPosition(position);//�����ǉ�
			ledgerline = true;
		}
	}
	else
	{
		for (LedgerLine* line : lineList)
		{//�������폜���邩�ǂ���
			D3DXVECTOR3 linePos = line->GetPosition();

			if (linePos.x == position.x && linePos.y != position.y)
			{
				line->SetDestroy();
				ledgerline = false;
				return;
			}
		}
	}

	//if (position.y = C + nextStaff * (system - 1))
	//{
	//	scene->AddObject<LedgerLine>(1)->SetPosition(position);//�����ǉ�

	//}

	if (Input::GetKeyTrigger(VK_SPACE))
	{//�X�y�[�X�L�[���������特��������
		//������z�u���Ă��̉��͉������L�^
		if (position.y == C)
		{
			scene->AddObject<LedgerLine>(1)->SetPosition(position);//�����ǉ�
		}

		if (!rest)
		{
			scene->AddObject<Note>(1)->Set(type, position);//�����m��
		}
		else
		{
			scene->AddObject<Rest>(1)->Set(type, position);//�����m��
		}
		
		//�ǂ̉��������f���đΉ�����������json�ŋL�^
		//���肵���Ƃ��ɂ��̉��𗬂�
		//�Q�s�ڂ��܂��ł��Ȃ�
		if (position.y == C1 || position.y == (C1 + (system * nextStaff)))
		{
			note[num].name = "C1";
			note[num].y = C1;

			noteSE[1]->Play();
		}
		else if (position.y == H)
		{
			note[num].name = "H";
			note[num].y = H;

			noteSE[2]->Play();
		}
		else if (position.y == A)
		{
			note[num].name = "A";
			note[num].y = A;

			noteSE[3]->Play();
		}
		else if (position.y == G)
		{
			note[num].name = "G";
			note[num].y = G;

			noteSE[4]->Play();
		}
		else if (position.y == F)
		{
			note[num].name = "F";
			note[num].y = F;

			noteSE[5]->Play();
		}
		else if (position.y == E)
		{
			note[num].name = "E";
			note[num].y = E;

			noteSE[6]->Play();
		}
		else if (position.y == D)
		{
			note[num].name = "D";
			note[num].y = D;

			noteSE[7]->Play();
		}
		else if (position.y == C)
		{
			note[num].name = "C";
			note[num].y = C;

			noteSE[8]->Play();
		}
		
		if (rest)
		{
			note[num].name = "rest";
			note[num].y = 70.0f + (nextStaff * (system - 1));

			_noteSE->Play();
		}

		note[num].id = num;

		note[num].type = type;


		//�ǂ̂��炢�E�Ɉړ����邩
		switch (type)
		{
		case whole:
			//num��8�̔{���ɂȂ����珬�ߐ��ǉ�
			if (num == (8 * barnum))
			{//num��8�̔{���ɂȂ�����
				D3DXVECTOR3 pos = position;
				pos.x += 370.0f;
				pos.y = 97.0f + (nextStaff * (system - 1));
				scene->AddObject<BarLine>(1)->SetPosition(pos);//���ߐ��ǉ�
				position.x += 40.0f;
				barnum++;
			}
			
			position.x += 90 * 4;
			num += 8;
			notenum += 8;
			break;

		case half:
			//num��8�̔{���ɂȂ����珬�ߐ��ǉ�
			if (num == (8 * barnum) + 4)
			{//num��8�̔{���ɂȂ�����
				D3DXVECTOR3 pos = position;
				pos.x += 200.0f;
				pos.y = 97.0f + (nextStaff * (system - 1));
				scene->AddObject<BarLine>(1)->SetPosition(pos);//���ߐ��ǉ�
				position.x += 30.0f;
				barnum++;
			}
			
			position.x += 90 * 2;
			num += 4;
			notenum += 4;
			break;

		case quarter:
			//num��8�̔{���ɂȂ����珬�ߐ��ǉ�
			if (num == (8 * barnum) + 6)
			{//num��8�̔{���ɂȂ�����
				D3DXVECTOR3 pos = position;
				pos.x += 100.0f;
				pos.y = 97.0f + (nextStaff * (system - 1));
				scene->AddObject<BarLine>(1)->SetPosition(pos);//���ߐ��ǉ�
				position.x += 40.0f;
				barnum++;
			}

			position.x += 90;
			num += 2;
			notenum += 2;
			break;

		case eighth:
			//num��8�̔{���ɂȂ����珬�ߐ��ǉ�
			if (num == (8 * barnum) + 7)
			{//num��8�̔{���ɂȂ�����
				D3DXVECTOR3 pos = position;
				pos.x += 80.0f;//���ߐ����E�ɂ��炵�Ĕz�u
				pos.y = 97.0f + (nextStaff * (system - 1));//���ߐ��̍���
				scene->AddObject<BarLine>(1)->SetPosition(pos);//���ߐ��ǉ�
				position.x += 30.0f;//���ߐ��̕����̉������E�ɂ��炷
				barnum++;
			}

			position.x += 90 / 2;
			num++;
			notenum++;
			break;

		default:
			break;
		}
	}

	if (!rest)
	{
		if (position.y <= H)
		{//�V�ȏ�̉���������
			//�����̌�����ύX
			tex[0] = { 1.0f, 1.0f };
			tex[1] = { 0.0f, 1.0f };
			tex[2] = { 1.0f, 0.0f };
			tex[3] = { 0.0f, 0.0f };
		}
		else
		{//���ȉ��̉���������
			//�����̌��������Ƃɖ߂�
			tex[0] = { 0.0f, 0.0f };
			tex[1] = { 1.0f, 0.0f };
			tex[2] = { 0.0f, 1.0f };
			tex[3] = { 1.0f, 1.0f };
		}
	}

	if (barnum == (system * 2))
	{//2�i�ڂɂȂ�����
		scene->AddObject<Staff>(1)->NewLine(system);//�ܐ����ǉ�
		scene->AddObject<TrebleClef>(1)->NextTrebleClef(system);//�g���L���ǉ�
		system++;
		position.y += nextStaff;
		position.x = startpos.x;//���ɖ߂�
	}

	//�t�@�C���o��
	std::ofstream os("notes.json", std::ios::out);//json�̃t�@�C���ɏo��
	cereal::JSONOutputArchive archiveFile(os);
	{
		archiveFile(cereal::make_nvp("notes", note));
	}


	//�ǂݍ��񂾏��ɉ���炷
	if (!play)return;

	////json�t�@�C���ǂݍ���
	//std::ifstream os("notes.json", std::ios::in);
	//cereal::JSONInputArchive archive(os);

	//noteLoad[num].serialize(archive);

	cnt++;

	if (cnt == length)
	{
		if (note[noteNum].name == "C1")
		{//�����̎�ނɂ���Ė炷����ς���
			noteSE[1]->Play();
		}
		else if (note[noteNum].name == "H")
		{
			noteSE[2]->Play();
		}
		else if (note[noteNum].name == "A")
		{
			noteSE[3]->Play();
		}
		else if (note[noteNum].name == "G")
		{
			noteSE[4]->Play();
		}
		else if (note[noteNum].name == "F")
		{
			noteSE[5]->Play();
		}
		else if (note[noteNum].name == "E")
		{
			noteSE[6]->Play();
		}
		else if (note[noteNum].name == "D")
		{
			noteSE[7]->Play();
		}
		else if(note[noteNum].name == "C")
		{
			noteSE[8]->Play();
		}

		cnt = 0;
		noteNum++;
	}

}

void Player::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���_�f�[�^
	vertex[0] = { D3DXVECTOR3(position.x          , position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[0].x, tex[0].y) };
	vertex[1] = { D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[1].x, tex[1].y) };
	vertex[2] = { D3DXVECTOR3(position.x          , position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[2].x, tex[2].y) };
	vertex[3] = { D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[3].x, tex[3].y) };

	//���_�o�b�t�@����
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	//�e�N�X�`���ݒ�
	if (!rest)
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &NoteTexture[type]);
	}
	else
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &RestTexture[type]);
	}

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}

