#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "input.h"

void Camera::Init()
{
	position = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Uninit()
{
}

void Camera::Update()
{
	//Player* player = Manager::GetScene()->GetObject<Player>(1);
	//target = player->GetPosition();

	////トップビュー
	//position = target + D3DXVECTOR3(0.0f, 5.0f, -8.0f);

	////サードパーソンビュー
	//D3DXVECTOR3 forward = player->GetForward();
	//position = target - forward * 5.0f + D3DXVECTOR3(0.0f, 3.0f, 0.0f);

	//if (Input::GetKeyPress(VK_UP))
	//{
	//	position.y -= 1.0f;
	//}
	//if (Input::GetKeyPress(VK_DOWN))
	//{
	//	position.y += 1.0f;
	//}

}

void Camera::Draw()
{
	//ビューマトリクス設定
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&ViewMatrix, &position, &target, &up);

	Renderer::SetViewMatrix(&ViewMatrix);

	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}
