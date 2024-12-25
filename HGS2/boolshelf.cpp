//----------------------------------------
//
//プレゼント処理[model.cpp]
//Author fuma sato
//
//----------------------------------------
#include"boolshelf.h"
#include"camera.h"
#include"input.h"
#include "particle.h"
#include "player.h"

// マクロ定義
#define X_NAME "data\\MODEL\\boolshelf.x"

//グローバル変数宣言
BoolShelf g_BoolShelf;
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitBoolShelf(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_BoolShelf.pos = D3DXVECTOR3(80.0f, 0.0f,-20.0f);
	g_BoolShelf.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BoolShelf.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BoolShelf.pBuffMat,
		NULL,
		&g_BoolShelf.dwNumMat,
		&g_BoolShelf.pMesh
	);

	//頂点数
	g_BoolShelf.nNumVtx = g_BoolShelf.pMesh->GetNumVertices();
	//頂点サイズ
	g_BoolShelf.sizeFVF = D3DXGetFVFVertexSize(g_BoolShelf.pMesh->GetFVF());
	//頂点バッファの取得
	g_BoolShelf.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_BoolShelf.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_BoolShelf.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_BoolShelf.pVtxBuff;

		if (vtx.x > g_BoolShelf.vtxMax.x)
		{
			g_BoolShelf.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_BoolShelf.vtxMin.x)
		{
			g_BoolShelf.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_BoolShelf.vtxMax.y)
		{
			g_BoolShelf.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_BoolShelf.vtxMin.y)
		{
			g_BoolShelf.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_BoolShelf.vtxMax.z)
		{
			g_BoolShelf.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_BoolShelf.vtxMin.z)
		{
			g_BoolShelf.vtxMin.z = vtx.z;
		}

		g_BoolShelf.pVtxBuff += g_BoolShelf.sizeFVF;
	}
	g_BoolShelf.Size.x = g_BoolShelf.vtxMax.x - g_BoolShelf.vtxMin.x;
	g_BoolShelf.Size.y = g_BoolShelf.vtxMax.y - g_BoolShelf.vtxMin.y;
	g_BoolShelf.Size.z = g_BoolShelf.vtxMax.z - g_BoolShelf.vtxMin.z;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_BoolShelf.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_BoolShelf.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_BoolShelf.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitBoolShelf(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_BoolShelf.apTexture[i]!=NULL)
		{
			g_BoolShelf.apTexture[i]->Release();
			g_BoolShelf.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_BoolShelf.pMesh != NULL)
	{
		g_BoolShelf.pMesh->Release();
		g_BoolShelf.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_BoolShelf.pBuffMat != NULL)
	{
		g_BoolShelf.pBuffMat->Release();
		g_BoolShelf.pBuffMat = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateBoolShelf(void)
{
	if (GetKeyboradTrigger(DIK_K) == true)
	{
		SetParticle(D3DXVECTOR3(g_BoolShelf.pos.x, g_BoolShelf.pos.y + 50.0f, g_BoolShelf.pos.z), D3DXVECTOR3(1.0f, 1.0f, 1.0f), PARTICLE_TYPE_COLLECT);
	}

	CollisionObj(g_BoolShelf.pos,g_BoolShelf.Size);
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawBoolShelf(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//マトリックス初期化
	D3DXMatrixIdentity(&g_BoolShelf.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_BoolShelf.scale.x, g_BoolShelf.scale.y, g_BoolShelf.scale.z);
	D3DXMatrixMultiply(&g_BoolShelf.mtxWorld, &g_BoolShelf.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_BoolShelf.rot.y, g_BoolShelf.rot.x, g_BoolShelf.rot.z);
	D3DXMatrixMultiply(&g_BoolShelf.mtxWorld, &g_BoolShelf.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_BoolShelf.pos.x, g_BoolShelf.pos.y, g_BoolShelf.pos.z);
	D3DXMatrixMultiply(&g_BoolShelf.mtxWorld, &g_BoolShelf.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_BoolShelf.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_BoolShelf.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_BoolShelf.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_BoolShelf.apTexture[nCntMat]);

		//モデル描画
		g_BoolShelf.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// 情報取得
//------------------------------
BoolShelf* GetBoolShelf(void)
{
	return &g_BoolShelf;
}

//------------------------------
// 情報設定
//------------------------------
void SetBoolShelfPos(D3DXVECTOR3 pos)
{
	g_BoolShelf.pos = pos;		// 位置設定
}
