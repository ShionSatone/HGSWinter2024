//=======================================
//
//　机 [chimney.cpp]
//　Author YOSHIDA YUTO
//
//=======================================

//***************************************
// インクルードファイル
//***************************************
#include"desk.h"
#include"camera.h"
#include"input.h"
#include "player.h"

//***************************************
// マクロ定義
//***************************************
#define X_NAME "data\\MODEL\\desk.x"

//***************************************
// グローバル変数宣言
//***************************************
Desk g_Desk;

//=======================================
// 机の初期化処理
//=======================================
void InitDesk(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Desk.pos = D3DXVECTOR3(-70.0f, 0.0f, 10.0f);
	g_Desk.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Desk.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Desk.pBuffMat,
		NULL,
		&g_Desk.dwNumMat,
		&g_Desk.pMesh
	);

	//頂点数
	g_Desk.nNumVtx = g_Desk.pMesh->GetNumVertices();
	//頂点サイズ
	g_Desk.sizeFVF = D3DXGetFVFVertexSize(g_Desk.pMesh->GetFVF());
	//頂点バッファの取得
	g_Desk.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Desk.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_Desk.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Desk.pVtxBuff;

		if (vtx.x > g_Desk.vtxMax.x)
		{
			g_Desk.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_Desk.vtxMin.x)
		{
			g_Desk.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_Desk.vtxMax.y)
		{
			g_Desk.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_Desk.vtxMin.y)
		{
			g_Desk.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_Desk.vtxMax.z)
		{
			g_Desk.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_Desk.vtxMin.z)
		{
			g_Desk.vtxMin.z = vtx.z;
		}

		g_Desk.pVtxBuff += g_Desk.sizeFVF;
	}
	g_Desk.Size.x = g_Desk.vtxMax.x - g_Desk.vtxMin.x;
	g_Desk.Size.y = g_Desk.vtxMax.y - g_Desk.vtxMin.y;
	g_Desk.Size.z = g_Desk.vtxMax.z - g_Desk.vtxMin.z;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Desk.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Desk.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Desk.apTexture[nCntMat]
			);
		}
	}
}
//=======================================
// 机の終了処理
//=======================================
void UninitDesk(void)
{
	//テクスチャの破棄
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (g_Desk.apTexture[i] != NULL)
		{
			g_Desk.apTexture[i]->Release();
			g_Desk.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_Desk.pMesh != NULL)
	{
		g_Desk.pMesh->Release();
		g_Desk.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_Desk.pBuffMat != NULL)
	{
		g_Desk.pBuffMat->Release();
		g_Desk.pBuffMat = NULL;
	}
}

//=======================================
// 机の更新処理
//=======================================
void UpdateDesk(void)
{
	CollisionObj(g_Desk.pos, g_Desk.Size);//プレイヤーとの当たり判定
}

//=======================================
// 机の描画処理
//=======================================
void DrawDesk(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//マトリックス初期化
	D3DXMatrixIdentity(&g_Desk.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_Desk.scale.x, g_Desk.scale.y, g_Desk.scale.z);
	D3DXMatrixMultiply(&g_Desk.mtxWorld, &g_Desk.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Desk.rot.y, g_Desk.rot.x, g_Desk.rot.z);
	D3DXMatrixMultiply(&g_Desk.mtxWorld, &g_Desk.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Desk.pos.x, g_Desk.pos.y, g_Desk.pos.z);
	D3DXMatrixMultiply(&g_Desk.mtxWorld, &g_Desk.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Desk.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Desk.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Desk.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_Desk.apTexture[nCntMat]);

		//モデル描画
		g_Desk.pMesh->DrawSubset(nCntMat);
	}

	//マテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//=======================================
// 机の取得処理
//=======================================
Desk* GetDesk(void)
{
	return &g_Desk;
}
//=======================================
// 机の設定処理
//=======================================
void SetDeskPos(D3DXVECTOR3 pos)
{
	g_Desk.pos = pos;
}
