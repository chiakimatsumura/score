
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "timeSignature.h"
#include "input.h"
#include "scene.h"
#include "note.h"
#include "effect.h"
#include "audio.h"

static D3D11_BUFFER_DESC bd{};
static D3D11_SUBRESOURCE_DATA sd{};

void TimeSignature::Init()
{
	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(
		Renderer::GetDevice(),
		"asset/texture/common-time.png",
		NULL,
		NULL,
		&Texture,
		NULL
	);

	assert(Texture);	//�G���[���������邽�߂̎d�g��
	//�f�o�b�O���s�̂Ƃ��Ƀe�N�X�`�����ǂݍ��߂������`�F�b�N���Ă����

	//�����_���[�N���X�̒��ɍ���Ă���֐����g���Ă�
	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Scene* scene = Manager::GetScene();

	_noteSE = scene->AddObject<Audio>(2);
	_noteSE->Load("asset\\sound\\se\\note.wav");

	position = { 20.0f,76.0f,0.0f };
	scale = { 190.0f,190.0f,0.0f };
}

void TimeSignature::Uninit()
{
	VertexBuffer->Release();
	Texture->Release();

	VertexLayout->Release();
	VertexShader->Release();
	PixelShader->Release();
}

void TimeSignature::Update()
{
}

void TimeSignature::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���_�f�[�^
	VERTEX_3D vertex[] =
	{
		{D3DXVECTOR3(position.x,           position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
		{D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
		{D3DXVECTOR3(position.x,           position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
		{D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)}
	};

	//���_�o�b�t�@����
	//D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

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

