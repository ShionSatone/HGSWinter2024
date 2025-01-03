//=======================================
//
//　煙突 [chimney.cpp]
//　Author YOSHIDA YUTO
//
//=======================================

//***************************************
// インクルードファイル
//***************************************
#include"chimney.h"
#include"camera.h"
#include"input.h"
#include "player.h"

//***************************************
// マクロ定義
//***************************************
#define X_NAME "data\\MODEL\\chimney.x"

//***************************************
// グローバル変数宣言
//***************************************
Chimney g_Chimney;

//=======================================
// 煙突の初期化処理
//=======================================
void InitChimney(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Chimney.pos = D3DXVECTOR3(0.0f, 0.0f, 110.0f);
	g_Chimney.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Chimney.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Chimney.pBuffMat,
		NULL,
		&g_Chimney.dwNumMat,
		&g_Chimney.pMesh
	);

	//頂点数
	g_Chimney.nNumVtx = g_Chimney.pMesh->GetNumVertices();
	//頂点サイズ
	g_Chimney.sizeFVF = D3DXGetFVFVertexSize(g_Chimney.pMesh->GetFVF());
	//頂点バッファの取得
	g_Chimney.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Chimney.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_Chimney.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Chimney.pVtxBuff;

		if (vtx.x > g_Chimney.vtxMax.x)
		{
			g_Chimney.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_Chimney.vtxMin.x)
		{
			g_Chimney.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_Chimney.vtxMax.y)
		{
			g_Chimney.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_Chimney.vtxMin.y)
		{
			g_Chimney.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_Chimney.vtxMax.z)
		{
			g_Chimney.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_Chimney.vtxMin.z)
		{
			g_Chimney.vtxMin.z = vtx.z;
		}

		g_Chimney.pVtxBuff += g_Chimney.sizeFVF;
	}
	g_Chimney.Size.x = g_Chimney.vtxMax.x - g_Chimney.vtxMin.x;
	g_Chimney.Size.y = g_Chimney.vtxMax.y - g_Chimney.vtxMin.y;
	g_Chimney.Size.z = g_Chimney.vtxMax.z - g_Chimney.vtxMin.z;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Chimney.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Chimney.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Chimney.apTexture[nCntMat]
			);
		}
	}
}
//=======================================
// 煙突の終了処理
//=======================================
void UninitChimney(void)
{
	//テクスチャの破棄
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (g_Chimney.apTexture[i] != NULL)
		{
			g_Chimney.apTexture[i]->Release();
			g_Chimney.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_Chimney.pMesh != NULL)
	{
		g_Chimney.pMesh->Release();
		g_Chimney.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_Chimney.pBuffMat != NULL)
	{
		g_Chimney.pBuffMat->Release();
		g_Chimney.pBuffMat = NULL;
	}
}

//=======================================
// 煙突の更新処理
//=======================================
void UpdateChimney(void)
{
	CollisionObj(g_Chimney.pos, g_Chimney.Size);//煙突とプレイヤーの当たり判定
}

//=======================================
// 煙突の描画処理
//=======================================
void DrawChimney(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//マトリックス初期化
	D3DXMatrixIdentity(&g_Chimney.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_Chimney.scale.x, g_Chimney.scale.y, g_Chimney.scale.z);
	D3DXMatrixMultiply(&g_Chimney.mtxWorld, &g_Chimney.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Chimney.rot.y, g_Chimney.rot.x, g_Chimney.rot.z);
	D3DXMatrixMultiply(&g_Chimney.mtxWorld, &g_Chimney.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Chimney.pos.x, g_Chimney.pos.y, g_Chimney.pos.z);
	D3DXMatrixMultiply(&g_Chimney.mtxWorld, &g_Chimney.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Chimney.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Chimney.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Chimney.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_Chimney.apTexture[nCntMat]);

		//モデル描画
		g_Chimney.pMesh->DrawSubset(nCntMat);
	}

	//マテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//=======================================
// 煙突の取得処理
//=======================================
Chimney* GetChimney(void)
{
	return &g_Chimney;
}
//=======================================
// 煙突の設定処理
//=======================================
void SetChimneyPos(D3DXVECTOR3 pos)
{
	g_Chimney.pos = pos;
}
