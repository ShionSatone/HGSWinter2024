//----------------------------------------
//
//靴下処理[socks.cpp]
//Author fuma sato
//
//----------------------------------------

#include"socks.h"
#include"camera.h"
#include"input.h"

// マクロ定義
#define X_NAME "data\\MODEL\\saku.x"

//グローバル変数宣言
Socks g_Socks;
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitSocks(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Socks.pos = D3DXVECTOR3(300.0f, 0.0f, 100.0f);
	g_Socks.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Socks.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Socks.pBuffMat,
		NULL,
		&g_Socks.dwNumMat,
		&g_Socks.pMesh
	);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Socks.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Socks.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Socks.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitSocks(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Socks.apTexture[i]!=NULL)
		{
			g_Socks.apTexture[i]->Release();
			g_Socks.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_Socks.pMesh != NULL)
	{
		g_Socks.pMesh->Release();
		g_Socks.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_Socks.pBuffMat != NULL)
	{
		g_Socks.pBuffMat->Release();
		g_Socks.pBuffMat = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateSocks(void)
{

}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawSocks(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//マトリックス初期化
	D3DXMatrixIdentity(&g_Socks.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_Socks.scale.x, g_Socks.scale.y, g_Socks.scale.z);
	D3DXMatrixMultiply(&g_Socks.mtxWorld, &g_Socks.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Socks.rot.y, g_Socks.rot.x, g_Socks.rot.z);
	D3DXMatrixMultiply(&g_Socks.mtxWorld, &g_Socks.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Socks.pos.x, g_Socks.pos.y, g_Socks.pos.z);
	D3DXMatrixMultiply(&g_Socks.mtxWorld, &g_Socks.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Socks.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Socks.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Socks.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_Socks.apTexture[nCntMat]);

		//モデル描画
		g_Socks.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// 情報取得
//------------------------------
Socks* GetSocks(void)
{
	return &g_Socks;
}

//------------------------------
// 情報設定
//------------------------------
void SetSocksPos(D3DXVECTOR3 pos)
{
	g_Socks.pos = pos;		// 位置設定
}