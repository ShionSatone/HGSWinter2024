//=======================================
//
//　ドア [door.cpp]
//　Author YOSHIDA YUTO
//
//=======================================

//***************************************
// インクルードファイル
//***************************************
#include"door.h"
#include"camera.h"
#include"input.h"
#include "santa.h"
#include "blacksanta.h"

//***************************************
// マクロ定義
//***************************************
#define X_NAME "data\\MODEL\\door.x"

//***************************************
// グローバル変数宣言
//***************************************
Door g_Door;

//=======================================
// ドアの初期化処理
//=======================================
void InitDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Door.pos = D3DXVECTOR3(-100.0f, 0.0f, 25.0f);
	g_Door.rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	g_Door.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Door.pBuffMat,
		NULL,
		&g_Door.dwNumMat,
		&g_Door.pMesh
	);
	//頂点数
	g_Door.nNumVtx = g_Door.pMesh->GetNumVertices();
	//頂点サイズ
	g_Door.sizeFVF = D3DXGetFVFVertexSize(g_Door.pMesh->GetFVF());
	//頂点バッファの取得
	g_Door.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Door.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_Door.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Door.pVtxBuff;

		if (vtx.x > g_Door.vtxMax.x)
		{
			g_Door.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_Door.vtxMin.x)
		{
			g_Door.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_Door.vtxMax.y)
		{
			g_Door.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_Door.vtxMin.y)
		{
			g_Door.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_Door.vtxMax.z)
		{
			g_Door.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_Door.vtxMin.z)
		{
			g_Door.vtxMin.z = vtx.z;
		}

		g_Door.pVtxBuff += g_Door.sizeFVF;
	}
	g_Door.Size.x = g_Door.vtxMax.x - g_Door.vtxMin.x;
	g_Door.Size.y = g_Door.vtxMax.y - g_Door.vtxMin.y;
	g_Door.Size.z = g_Door.vtxMax.z - g_Door.vtxMin.z;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Door.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Door.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Door.apTexture[nCntMat]
			);
		}
	}
}
//=======================================
// ドアの終了処理
//=======================================
void UninitDoor(void)
{
	//テクスチャの破棄
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (g_Door.apTexture[i] != NULL)
		{
			g_Door.apTexture[i]->Release();
			g_Door.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_Door.pMesh != NULL)
	{
		g_Door.pMesh->Release();
		g_Door.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_Door.pBuffMat != NULL)
	{
		g_Door.pBuffMat->Release();
		g_Door.pBuffMat = NULL;
	}
}

//=======================================
// ドアの更新処理
//=======================================
void UpdateDoor(void)
{
	Santa* pSanta = GetSanta();//サンタを取得
	BlackSanta* pBlacSanta = GetBlackSanta();

	if (pSanta->Startpos.z == g_Door.pos.z && pSanta->bUse == true || pBlacSanta->pos.z == g_Door.pos.z && pBlacSanta->bUse == true)
	{//サンタが使われている
		g_Door.rotDest.y = 0.0f; //ドアが空いた
	}
	else
	{
		g_Door.rotDest.y = D3DX_PI * 0.5f;//ドアがしまった
	}

	g_Door.rot.y += (g_Door.rotDest.y - g_Door.rot.y) * 0.05f;//ドアの向きを目的の向きにする

	CollisionObj(g_Door.pos, g_Door.Size);
}

//=======================================
// ドアの描画処理
//=======================================
void DrawDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//マトリックス初期化
	D3DXMatrixIdentity(&g_Door.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_Door.scale.x, g_Door.scale.y, g_Door.scale.z);
	D3DXMatrixMultiply(&g_Door.mtxWorld, &g_Door.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Door.rot.y, g_Door.rot.x, g_Door.rot.z);
	D3DXMatrixMultiply(&g_Door.mtxWorld, &g_Door.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Door.pos.x, g_Door.pos.y, g_Door.pos.z);
	D3DXMatrixMultiply(&g_Door.mtxWorld, &g_Door.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Door.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Door.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Door.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_Door.apTexture[nCntMat]);

		//モデル描画
		g_Door.pMesh->DrawSubset(nCntMat);
	}

	//マテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//=======================================
// ドアの取得処理
//=======================================
Door* GetDoor(void)
{
	return &g_Door;
}
//=======================================
// ドアの設定処理
//=======================================
void SetDoorPos(D3DXVECTOR3 pos)
{
	g_Door.pos = pos;
}
