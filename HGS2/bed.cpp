//----------------------------------------
//
//プレゼント処理[model.cpp]
//Author fuma sato
//
//----------------------------------------

#include"present.h"
#include"camera.h"
#include"input.h"

#if 0
// マクロ定義
#define X_NAME "data\\MODEL\\prezent.x"

//グローバル変数宣言
Present g_Present;
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitPresent(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Present.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Present.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Present.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Present.pBuffMat,
		NULL,
		&g_Present.dwNumMat,
		&g_Present.pMesh
	);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Present.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Present.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Present.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitPresent(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Present.apTexture[i]!=NULL)
		{
			g_Present.apTexture[i]->Release();
			g_Present.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_Present.pMesh != NULL)
	{
		g_Present.pMesh->Release();
		g_Present.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_Present.pBuffMat != NULL)
	{
		g_Present.pBuffMat->Release();
		g_Present.pBuffMat = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdatePresent(void)
{

}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawPresent(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//マトリックス初期化
	D3DXMatrixIdentity(&g_Present.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_Present.scale.x, g_Present.scale.y, g_Present.scale.z);
	D3DXMatrixMultiply(&g_Present.mtxWorld, &g_Present.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Present.rot.y, g_Present.rot.x, g_Present.rot.z);
	D3DXMatrixMultiply(&g_Present.mtxWorld, &g_Present.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Present.pos.x, g_Present.pos.y, g_Present.pos.z);
	D3DXMatrixMultiply(&g_Present.mtxWorld, &g_Present.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Present.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Present.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Present.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_Present.apTexture[nCntMat]);

		//モデル描画
		g_Present.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// 情報取得
//------------------------------
Present* GetPresent(void)
{
	return &g_Present;
}

//------------------------------
// 情報設定
//------------------------------
void SetPresentPos(D3DXVECTOR3 pos)
{
	g_Present.pos = pos;		// 位置設定
}
#endif