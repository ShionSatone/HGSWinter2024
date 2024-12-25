//----------------------------------------
//
//プレゼント処理[model.cpp]
//Author fuma sato
//
//----------------------------------------

#include"field.h"
#include"camera.h"
#include"input.h"
#include "particle.h"
#include "player.h"

// マクロ定義
#define X_NAME "data\\MODEL\\yuka.x"

//グローバル変数宣言
Field g_Field;
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Field.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_Field.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Field.pBuffMat,
		NULL,
		&g_Field.dwNumMat,
		&g_Field.pMesh
	);

	//頂点数
	g_Field.nNumVtx = g_Field.pMesh->GetNumVertices();
	//頂点サイズ
	g_Field.sizeFVF = D3DXGetFVFVertexSize(g_Field.pMesh->GetFVF());
	//頂点バッファの取得
	g_Field.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Field.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_Field.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Field.pVtxBuff;

		if (vtx.x > g_Field.vtxMax.x)
		{
			g_Field.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_Field.vtxMin.x)
		{
			g_Field.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_Field.vtxMax.y)
		{
			g_Field.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_Field.vtxMin.y)
		{
			g_Field.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_Field.vtxMax.z)
		{
			g_Field.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_Field.vtxMin.z)
		{
			g_Field.vtxMin.z = vtx.z;
		}

		g_Field.pVtxBuff += g_Field.sizeFVF;
	}
	g_Field.Size.x = g_Field.vtxMax.x - g_Field.vtxMin.x;
	g_Field.Size.y = g_Field.vtxMax.y - g_Field.vtxMin.y;
	g_Field.Size.z = g_Field.vtxMax.z - g_Field.vtxMin.z;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Field.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Field.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャがある
			//テクスチャの読み込み
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Field.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitField(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Field.apTexture[i]!=NULL)
		{
			g_Field.apTexture[i]->Release();
			g_Field.apTexture[i] = NULL;
		}
	}
	//メッシュの破棄
	if (g_Field.pMesh != NULL)
	{
		g_Field.pMesh->Release();
		g_Field.pMesh = NULL;
	}
	//マテリアルの破棄
	if (g_Field.pBuffMat != NULL)
	{
		g_Field.pBuffMat->Release();
		g_Field.pBuffMat = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateField(void)
{
	//CollisionObj(g_Field.pos,g_Field.Size);//当たり判定
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//マトリックス初期化
	D3DXMatrixIdentity(&g_Field.mtxWorld);

	//大きさの反映
	D3DXMatrixScaling(&mtxScale, g_Field.scale.x, g_Field.scale.y, g_Field.scale.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field.rot.y, g_Field.rot.x, g_Field.rot.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Field.pos.x, g_Field.pos.y, g_Field.pos.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Field.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Field.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Field.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャ
		pDevice->SetTexture(0, g_Field.apTexture[nCntMat]);

		//モデル描画
		g_Field.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// 情報取得
//------------------------------
Field* GetField(void)
{
	return &g_Field;
}

//------------------------------
// 情報設定
//------------------------------
void SetFieldPos(D3DXVECTOR3 pos)
{
	g_Field.pos = pos;		// 位置設定
}

void CollisionField(void)
{
}
