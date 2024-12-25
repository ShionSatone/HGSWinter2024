//=======================================
//
//　椅子 [chair.cpp]
//　Author YOSHIDA YUTO
//
//=======================================

//***************************************
// インクルードファイル
//***************************************
#include"chair.h"
#include"camera.h"
#include"input.h"

//***************************************
// マクロ定義
//***************************************
#define X_NAME "data\\MODEL\\chair.x"

//***************************************
// グローバル変数宣言
//***************************************
Chair g_Chair;

//=======================================
// 椅子の初期化処理
//=======================================
void InitChair(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Chair.pos = D3DXVECTOR3(-40.0f, 0.0f, 0.0f);
	g_Chair.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Chair.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Chair.pBuffMat,
		NULL,
		&g_Chair.dwNumMat,
		&g_Chair.pMesh
	);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Chair.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Chair.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Chair.apTexture[nCntMat]
			);
		}
	}
}
//=======================================
// 椅子の終了処理
//=======================================
void UninitChair(void)
{
	//テクスチャの破棄
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (g_Chair.apTexture[i] != NULL)
		{
			g_Chair.apTexture[i]->Release();
			g_Chair.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_Chair.pMesh != NULL)
	{
		g_Chair.pMesh->Release();
		g_Chair.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_Chair.pBuffMat != NULL)
	{
		g_Chair.pBuffMat->Release();
		g_Chair.pBuffMat = NULL;
	}
}

//=======================================
// 椅子の更新処理
//=======================================
void UpdateChair(void)
{

}

//=======================================
// 椅子の描画処理
//=======================================
void DrawChair(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//マトリックス初期化
	D3DXMatrixIdentity(&g_Chair.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_Chair.scale.x, g_Chair.scale.y, g_Chair.scale.z);
	D3DXMatrixMultiply(&g_Chair.mtxWorld, &g_Chair.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Chair.rot.y, g_Chair.rot.x, g_Chair.rot.z);
	D3DXMatrixMultiply(&g_Chair.mtxWorld, &g_Chair.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Chair.pos.x, g_Chair.pos.y, g_Chair.pos.z);
	D3DXMatrixMultiply(&g_Chair.mtxWorld, &g_Chair.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Chair.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Chair.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Chair.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_Chair.apTexture[nCntMat]);

		//モデル描画
		g_Chair.pMesh->DrawSubset(nCntMat);
	}

	//マテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//=======================================
// 椅子の取得処理
//=======================================
Chair* GetChair(void)
{
	return &g_Chair;
}
//=======================================
// 椅子の設定処理
//=======================================
void SetChairPos(D3DXVECTOR3 pos)
{
	g_Chair.pos = pos;
}
