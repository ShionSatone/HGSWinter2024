//----------------------------------------
//
//プレゼント処理[model.cpp]
//Author fuma sato
//
//----------------------------------------

#include"bed.h"
#include"camera.h"
#include"input.h"
#include "particle.h"
#include "player.h"

// マクロ定義
#define X_NAME "data\\MODEL\\bed.x"

//グローバル変数宣言
Bed g_Bed;
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitBed(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Bed.pos = D3DXVECTOR3(190.0f, 0.0f, -40.0f);
	g_Bed.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Bed.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Bed.pBuffMat,
		NULL,
		&g_Bed.dwNumMat,
		&g_Bed.pMesh
	);

	//頂点数
	g_Bed.nNumVtx = g_Bed.pMesh->GetNumVertices();
	//頂点サイズ
	g_Bed.sizeFVF = D3DXGetFVFVertexSize(g_Bed.pMesh->GetFVF());
	//頂点バッファの取得
	g_Bed.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Bed.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_Bed.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Bed.pVtxBuff;

		if (vtx.x > g_Bed.vtxMax.x)
		{
			g_Bed.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_Bed.vtxMin.x)
		{
			g_Bed.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_Bed.vtxMax.y)
		{
			g_Bed.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_Bed.vtxMin.y)
		{
			g_Bed.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_Bed.vtxMax.z)
		{
			g_Bed.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_Bed.vtxMin.z)
		{
			g_Bed.vtxMin.z = vtx.z;
		}

		g_Bed.pVtxBuff += g_Bed.sizeFVF;
	}
	g_Bed.Size.x = g_Bed.vtxMax.x - g_Bed.vtxMin.x;
	g_Bed.Size.y = g_Bed.vtxMax.y - g_Bed.vtxMin.y;
	g_Bed.Size.z = g_Bed.vtxMax.z - g_Bed.vtxMin.z;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Bed.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Bed.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Bed.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitBed(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Bed.apTexture[i]!=NULL)
		{
			g_Bed.apTexture[i]->Release();
			g_Bed.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_Bed.pMesh != NULL)
	{
		g_Bed.pMesh->Release();
		g_Bed.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_Bed.pBuffMat != NULL)
	{
		g_Bed.pBuffMat->Release();
		g_Bed.pBuffMat = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateBed(void)
{
	if (GetKeyboradTrigger(DIK_K) == true)
	{
		SetParticle(D3DXVECTOR3(g_Bed.pos.x, g_Bed.pos.y + 50.0f, g_Bed.pos.z), D3DXVECTOR3(1.0f, 1.0f, 1.0f), PARTICLE_TYPE_COLLECT);
	}

	CollisionObj(g_Bed.pos,g_Bed.Size);//当たり判定
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawBed(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//マトリックス初期化
	D3DXMatrixIdentity(&g_Bed.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_Bed.scale.x, g_Bed.scale.y, g_Bed.scale.z);
	D3DXMatrixMultiply(&g_Bed.mtxWorld, &g_Bed.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Bed.rot.y, g_Bed.rot.x, g_Bed.rot.z);
	D3DXMatrixMultiply(&g_Bed.mtxWorld, &g_Bed.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Bed.pos.x, g_Bed.pos.y, g_Bed.pos.z);
	D3DXMatrixMultiply(&g_Bed.mtxWorld, &g_Bed.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Bed.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Bed.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Bed.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_Bed.apTexture[nCntMat]);

		//モデル描画
		g_Bed.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// 情報取得
//------------------------------
Bed* GetBed(void)
{
	return &g_Bed;
}

//------------------------------
// 情報設定
//------------------------------
void SetBedPos(D3DXVECTOR3 pos)
{
	g_Bed.pos = pos;		// 位置設定
}

void CollisionBed(void)
{
}
