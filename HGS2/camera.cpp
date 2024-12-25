//----------------------------------------
//
//カメラ処理[camera.cpp]
//Author fuma sato
//
//----------------------------------------

#include"camera.h"

//グローバル変数宣言
Camera g_camera;//カメラ情報
//----------------------
//初期化処理
//----------------------
void InitCamera(void)
{
	//カメラ設定
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -150.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_camera.rot = D3DXVECTOR3(-atan2f(120.0f, 300.0f), 0.0f, 0.0f);
}

//-------------------
//終了処理
//-------------------
void UninitCamera(void)
{

}

//-------------------
//更新処理
//-------------------
void UpdateCamera(void)
{

}

//-------------------
//描画処理
//-------------------
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();
	//ビューマトリックス初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH
	(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.posU
	);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックス初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH
	(
		&g_camera.mtxProjection,
		D3DXToRadian(CAMERA_WIDTH),//視界の広さ
		(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,//比率
		CAMERA_MIN,//どこから
		CAMERA_MAX//どこまで
	);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//--------------------------
//カメラ取得
//--------------------------
Camera* GetCamera(void)
{
	return &g_camera;
}