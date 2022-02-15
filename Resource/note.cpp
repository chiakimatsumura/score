
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "note.h"
#include "input.h"
#include "scene.h"

#include "ledgerLine.h"

VERTEX_3D g_noteVertex[4];
static D3D11_BUFFER_DESC bd{};
static D3D11_SUBRESOURCE_DATA sd{};


void Note::Init()
{
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


	//�����_���[�N���X�̒��ɍ���Ă���֐����g���Ă�
	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	position = { 0.0f,130.0f,0.0f };
	scale = { 190.0f,190.0f,0.0f };

	tex[0] = { 0.0f, 0.0f };
	tex[1] = { 1.0f, 0.0f };
	tex[2] = { 0.0f, 1.0f };
	tex[3] = { 1.0f, 1.0f };
}

void Note::Uninit()
{
	VertexBuffer->Release();

	for (int i = 0; i < 3; i++)
	{
		NoteTexture[i]->Release();
	}

	VertexLayout->Release();
	VertexShader->Release();
	PixelShader->Release();
}

void Note::Update()
{

}

void Note::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();


	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void Note::Set(int type, D3DXVECTOR3 pos)
{
	switch (type)
	{
	case whole:
		Texture = NoteTexture[whole];
		break;

	case half:
		Texture = NoteTexture[half];
		break;

	case quarter:
		Texture = NoteTexture[quarter];
		break;

	case eighth:
		Texture = NoteTexture[eighth];
		break;

	default:
		break;
	}

	position = pos;

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


	//���_�f�[�^
	g_noteVertex[0] = { D3DXVECTOR3(position.x          , position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[0].x, tex[0].y) };
	g_noteVertex[1] = { D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[1].x, tex[1].y) };
	g_noteVertex[2] = { D3DXVECTOR3(position.x          , position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[2].x, tex[2].y) };
	g_noteVertex[3] = { D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(tex[3].x, tex[3].y) };


	//���_�o�b�t�@����
	//D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = g_noteVertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);
}
