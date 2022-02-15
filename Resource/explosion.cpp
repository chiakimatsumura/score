//#include "main.h"
//#include "renderer.h"
//#include "manager.h"
//#include "scene.h"
//#include "explosion.h"
//#include "camera.h"
//
//void Explosion::Init()
//{
//	VERTEX_3D vertex[4];
//
//	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
//	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
//
//	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
//	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
//
//	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
//	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
//
//	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
//	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
//
//	//���_�o�b�t�@����
//	D3D11_BUFFER_DESC bd;
//	ZeroMemory(&bd, sizeof(bd));
//	bd.Usage = D3D11_USAGE_DYNAMIC;//���_�o�b�t�@�̏����������ł���悤��
//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���_�o�b�t�@�̏����������ł���悤��
//	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//���_�o�b�t�@�̏����������ł���悤��
//	//�����ς��Ȃ��Ă��G���[�͏o�Ȃ����ǎ��s����Ƃł��Ȃ�
//
//	D3D11_SUBRESOURCE_DATA sd;
//	ZeroMemory(&sd, sizeof(sd));
//	sd.pSysMem = vertex;
//
//	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);
//
//	//�e�N�X�`���ǂݍ���
//	D3DX11CreateShaderResourceViewFromFile
//	(
//		Renderer::GetDevice(),
//		"asset/texture/explosion.png",
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
//	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");//���C�e�B���O����
//	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");//���C�e�B���O����
//
//
//	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//
//	count = 0;
//}
//
//void Explosion::Uninit()
//{
//	VertexBuffer->Release();
//	Texture->Release();
//
//	VertexLayout->Release();
//	VertexShader->Release();
//	PixelShader->Release();
//}
//
//void Explosion::Update()
//{
//	count++;
//	if (count >= 16)
//	{
//		SetDestroy();
//		return;
//	}
//}
//
//void Explosion::Draw()
//{
//	//�e�N�X�`�����W�Z�o
//	float x = count % 4 * (1.0f / 4);
//	float y = count / 4 * (1.0f / 4);
//
//	//���_�f�[�^��������
//	D3D11_MAPPED_SUBRESOURCE msr;
//	Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
//
//	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
//
//	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
//	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[0].TexCoord = D3DXVECTOR2(x, y);
//
//	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
//	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[1].TexCoord = D3DXVECTOR2(x + 0.25f, y);
//
//	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
//	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[2].TexCoord = D3DXVECTOR2(x, y + 0.25f);
//
//	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
//	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[3].TexCoord = D3DXVECTOR2(x + 0.25f, y + 0.25f);
//
//	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);
//
//	//���̓��C�A�E�g�ݒ�
//	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);
//
//	//�V�F�[�_�ݒ�
//	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
//	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);
//
//	//�J�����̃r���[�}�g���N�X�擾
//	Scene* scene = Manager::GetScene();
//	Camera* camera = scene->GetObj<Camera>(0);
//	D3DXMATRIX view = camera->GetViewMatrix();
//
//	//�r���[�̋t�s��
//	D3DXMATRIX invView;
//	D3DXMatrixInverse(&invView, NULL, &view);//�t�s��
//	invView._41 = 0.0f;
//	invView._42 = 0.0f;
//	invView._43 = 0.0f;
//	//�ړ���0.0f�ɂ��Ă���
//
//	//���[���h�}�g���N�X�ݒ�
//	D3DXMATRIX world, sca, trans;
//	D3DXMatrixScaling(&sca, scale.x, scale.y, scale.z);
//	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);
//	world = sca * invView * trans;	//�}���`�v���C�Ƃ����v�Z�ō���
//	Renderer::SetWorldMatrix(&world);
//
//	//���_�o�b�t�@�ݒ�
//	UINT stride = sizeof(VERTEX_3D);
//	UINT offset = 0;
//	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
//
//	//�}�e���A���ݒ�
//	MATERIAL material;
//	ZeroMemory(&material, sizeof(material));
//	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	Renderer::SetMaterial(material);
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
