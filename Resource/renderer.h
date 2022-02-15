#pragma once





struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;
};



struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];
};



struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
};



class Renderer
{//レンダラークラス
	//DirectXの描画を管理する
private:

	//staticをつけるとインスタンス(new)を作らなくても関数にアクセスできる
	//でもcppの最初で宣言しないと使えない
	//プロパティ、メンバ変数
	static D3D_FEATURE_LEVEL       FeatureLevel;

	static ID3D11Device*           Device;
	static ID3D11DeviceContext*    DeviceContext;
	static IDXGISwapChain*         SwapChain;
	static ID3D11RenderTargetView* RenderTargetView;
	static ID3D11DepthStencilView* DepthStencilView;

	static ID3D11Buffer*			WorldBuffer;
	static ID3D11Buffer*			ViewBuffer;
	static ID3D11Buffer*			ProjectionBuffer;
	static ID3D11Buffer*			MaterialBuffer;
	static ID3D11Buffer*			LightBuffer;


	static ID3D11DepthStencilState* DepthStateEnable;
	static ID3D11DepthStencilState* DepthStateDisable;




public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);

	static ID3D11Device* GetDevice( void ){ return Device; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return DeviceContext; }



	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);


};
