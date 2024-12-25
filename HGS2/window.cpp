//----------------------------------------
//
//窓処理[window.cpp]
//Author fuma sato
//
//----------------------------------------

#include"window.h"
#include"camera.h"
#include"input.h"
#include "particle.h"

// マクロ定義
#define X_NAME "data\\MODEL\\window.x"

//グローバル変数宣言
Window g_Window;
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitWindow(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Window.pos = D3DXVECTOR3(0.0f, 0.0f, -130.0f);
	g_Window.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Window.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Window.pBuffMat,
		NULL,
		&g_Window.dwNumMat,
		&g_Window.pMesh
	);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Window.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Window.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Window.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitWindow(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Window.apTexture[i]!=NULL)
		{
			g_Window.apTexture[i]->Release();
			g_Window.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_Window.pMesh != NULL)
	{
		g_Window.pMesh->Release();
		g_Window.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_Window.pBuffMat != NULL)
	{
		g_Window.pBuffMat->Release();
		g_Window.pBuffMat = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateWindow(void)
{
	if (GetKeyboradTrigger(DIK_K) == true)
	{
		SetParticle(D3DXVECTOR3(g_Window.pos.x, g_Window.pos.y + 50.0f, g_Window.pos.z), D3DXVECTOR3(1.0f, 1.0f, 1.0f), PARTICLE_TYPE_COLLECT);
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawWindow(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//マトリックス初期化
	D3DXMatrixIdentity(&g_Window.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_Window.scale.x, g_Window.scale.y, g_Window.scale.z);
	D3DXMatrixMultiply(&g_Window.mtxWorld, &g_Window.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Window.rot.y, g_Window.rot.x, g_Window.rot.z);
	D3DXMatrixMultiply(&g_Window.mtxWorld, &g_Window.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Window.pos.x, g_Window.pos.y, g_Window.pos.z);
	D3DXMatrixMultiply(&g_Window.mtxWorld, &g_Window.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Window.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Window.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Window.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_Window.apTexture[nCntMat]);

		//モデル描画
		g_Window.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// 情報取得
//------------------------------
Window* GetWindow(void)
{
	return &g_Window;
}

//------------------------------
// 情報設定
//------------------------------
void SetWindowPos(D3DXVECTOR3 pos)
{
	g_Window.pos = pos;		// 位置設定
}