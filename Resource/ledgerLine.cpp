
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "ledgerLine.h"
#include "input.h"
#include "scene.h"
#include "note.h"
#include "effect.h"
#include "audio.h"
static D3D11_BUFFER_DESC bd{};
static D3D11_SUBRESOURCE_DATA sd{};

void LedgerLine::Init()
{
	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(
		Renderer::GetDevice(),
		"asset/texture/ledger-line.png",
		NULL,
		NULL,
		&Texture,
		NULL
	);

	assert(Texture);	//�G���[���������邽�߂̎d�g��
	//�f�o�b�O���s�̂Ƃ��Ƀe�N�X�`�����ǂݍ��߂������`�F�b�N���Ă����

	//	//���_�f�[�^
	//VERTEX_3D vertex[] =
	//{
	//	{D3DXVECTOR3(position.x,           position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
	//	{D3DXVECTOR3(position.x + scale.x, position.y,           0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
	//	{D3DXVECTOR3(position.x,           position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
	//	{D3DXVECTOR3(position.x + scale.x, position.y + scale.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)}
	//};

	////���_�o�b�t�@����
	//D3D11_BUFFER_DESC bd{};
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd{};
	//sd.pSysMem = vertex;

	//Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);


	//�����_���[�N���X�̒��ɍ���Ă���֐����g���Ă�
	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Scene* scene = Manager::GetScene();

	_noteSE = scene->AddObject<Audio>(2);
	_noteSE->Load("asset\\sound\\se\\note.wav");

	position = { 0.0f,130.0f,0.0f };
	scale = { 190.0f,190.0f,0.0f };
}

void LedgerLine::Uninit()
{
	VertexBuffer->Release();
	Texture->Release();

	VertexLayout->Release();
	VertexShader->Release();
	PixelShader->Release();
}

void LedgerLine::Update()
{
	//if (Input::GetKeyTrigger('W'))
	//{
	//	position.y -= 11.0f;
	//}
	//
	//if (Input::GetKeyTrigger('S'))
	//{
	//	position.y += 11.0f;
	//}

	//if (position.y <= C1)
	//{
	//	position.y = C1;
	//}

	//if (position.y >= C)
	//{
	//	position.y = C;
	//}

	//if (position.y < C)
	//{
	//	SetDestroy();//�����\��
	//}

	//Scene* scene = Manager::GetScene();
	//std::vector<Note*>noteList = scene->GetObjects<Note>(1);//�����̏����擾

	////if (Input::GetKeyTrigger(VK_SPACE))
	//{
	//	for (Note* note : noteList)
	//	{//�����Ƃ̓����蔻��
	//		D3DXVECTOR3 notePosition = note->GetPosition();

	//		if (position.x + 170.0f >= notePosition.x && position.x + 120.0f <= notePosition.x && position.y == notePosition.y)
	//		{//�v���C���[�Ɖ������������Ă��邩
	//			if (Input::GetKeyTrigger(VK_SPACE))
	//			{//�X�y�[�X�L�[����������
	//				scene->AddObject<Effect>(1)->SetPosition(notePosition);//�G�t�F�N�g�\��

	//				//_noteSE->Play();

	//				note->SetDestroy();

	//				return;
	//			}
	//		}
	//	}
	//}
}

void LedgerLine::Draw()
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
