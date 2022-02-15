//
//#include "main.h"
//#include "renderer.h"
//#include "effect.h"
//
//
//void Effect::Init()
//{
//	//�e�N�X�`���ǂݍ���
//	D3DX11CreateShaderResourceViewFromFile
//	(
//		Renderer::GetDevice(),
//		"asset/texture/effect.png",
//		NULL,
//		NULL,
//		&Texture,
//		NULL
//	);
//
//	assert(Texture);	//�G���[���������邽�߂̎d�g��
//	//�f�o�b�O���s�̂Ƃ��Ƀe�N�X�`�����ǂݍ��߂������`�F�b�N���Ă����
//
//	//�����_���[�N���X�̒��ɍ���Ă���֐����g���Ă�
//	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
//	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");
//
//	position = { 0.0f,0.0f,0.0f };
//	scale = { 300.0f,300.0f,0.0f };
//	rotation = { 0.0f,0.0f,0.0f };
//}
//
//void Effect::Uninit()
//{
//	VertexBuffer->Release();
//	Texture->Release();
//
//	VertexLayout->Release();
//	VertexShader->Release();
//	PixelShader->Release();
//}
//
//void Effect::Update()
//{
//	rotation.x += 8.0f;
//	rotation.y += 8.0f;
//	count++;
//	if (count >= 13)
//	{
//		SetDestroy();
//		return;
//	}
//}
//
//void Effect::Draw()
//{
//	//���̓��C�A�E�g�ݒ�
//	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);
//
//	//�V�F�[�_�ݒ�
//	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
//	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);
//
//	//�}�g���N�X�ݒ�
//	Renderer::SetWorldViewProjection2D();
//
//	//���_�f�[�^
//	VERTEX_3D vertex[] =
//	{
//		{D3DXVECTOR3(position.x           + rotation.x, position.y           - rotation.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
//		{D3DXVECTOR3(position.x + scale.x + rotation.x, position.y           + rotation.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
//		{D3DXVECTOR3(position.x           - rotation.x, position.y + scale.y - rotation.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
//		{D3DXVECTOR3(position.x + scale.x - rotation.x, position.y + scale.y + rotation.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)}
//	};
//
//	//���_�o�b�t�@����
//	D3D11_BUFFER_DESC bd{};
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//
//	D3D11_SUBRESOURCE_DATA sd{};
//	sd.pSysMem = vertex;
//
//	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);
//
//	//���_�o�b�t�@�ݒ�
//	UINT stride = sizeof(VERTEX_3D);
//	UINT offset = 0;
//	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
//
//	//�e�N�X�`���ݒ�
//	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);
//
//	//�v���~�e�B�u�g�|���W�ݒ�
//	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	//�|���S���`��
//	Renderer::GetDeviceContext()->Draw(4, 0);
//}
