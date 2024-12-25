//----------------------------------------
//
//壁処理[wall.cpp]
//Author fuma sato
//
//----------------------------------------

#include"wall.h"
#include"camera.h"
#include"input.h"
#include "particle.h"

// マクロ定義
#define X_NAME "data\\MODEL\\madowindow.x"
#define NUM_FILE	(4)

//グローバル変数宣言
Wall g_Wall[NUM_FILE];

const char* file[NUM_FILE] =
{
	"data\\MODEL\\madowindow.x",
	"data\\MODEL\\wall1.x"
};

//----------------------
//ポリゴンの初期化処理
//----------------------
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Wall[0].pos = D3DXVECTOR3(0.0f, 0.0f, -130.0f);
	g_Wall[1].pos = D3DXVECTOR3(0.0f, 0.0f, 130.0f);
	g_Wall[2].pos = D3DXVECTOR3(250.0f, 0.0f, 0.0f);
	g_Wall[2].rot = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f);
	g_Wall[3].pos = D3DXVECTOR3(-250.0f, 0.0f, 0.0f);
	g_Wall[3].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);

	for (int i = 0; i < NUM_FILE; i++)
	{
		g_Wall[i].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		if (i == 0)
		{
			//Xファイル読み込み
			D3DXLoadMeshFromX
			(
				"data\\MODEL\\madowindow.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Wall[i].pBuffMat,
				NULL,
				&g_Wall[i].dwNumMat,
				&g_Wall[i].pMesh
			);
		}
		else if (i == 1)
		{
			//Xファイル読み込み
			D3DXLoadMeshFromX
			(
				"data\\MODEL\\wall1.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Wall[i].pBuffMat,
				NULL,
				&g_Wall[i].dwNumMat,
				&g_Wall[i].pMesh
			);
		}
		else if (i == 2)
		{
			//Xファイル読み込み
			D3DXLoadMeshFromX
			(
				"data\\MODEL\\bedwall.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Wall[i].pBuffMat,
				NULL,
				&g_Wall[i].dwNumMat,
				&g_Wall[i].pMesh
			);
		}
		else if (i == 3)
		{
			//Xファイル読み込み
			D3DXLoadMeshFromX
			(
				"data\\MODEL\\doowwall.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Wall[i].pBuffMat,
				NULL,
				&g_Wall[i].dwNumMat,
				&g_Wall[i].pMesh
			);
		}

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Wall[i].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Wall[i].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャがある
				//テクスチャの読み込み
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Wall[i].apTexture[nCntMat]
				);
			}
		}
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitWall(void)
{
	for (int nCnt = 0; nCnt < NUM_FILE; nCnt++)
	{
		for (int i = 0; i < 64; i++)
		{
			if (g_Wall[nCnt].apTexture[i] != NULL)
			{
				g_Wall[nCnt].apTexture[i]->Release();
				g_Wall[nCnt].apTexture[i] = NULL;
			}
		}

		//メッシュの破棄
		if (g_Wall[nCnt].pMesh != NULL)
		{
			g_Wall[nCnt].pMesh->Release();
			g_Wall[nCnt].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_Wall[nCnt].pBuffMat != NULL)
		{
			g_Wall[nCnt].pBuffMat->Release();
			g_Wall[nCnt].pBuffMat = NULL;
		}

		for (int i = 0; i < NUM_FILE; i++)
		{
			if (file[i] != NULL)
			{
				file[i] = NULL;
			}
		}
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateWall(void)
{
	
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int i = 0; i < NUM_FILE; i++)
	{
		//マトリックス初期化
		D3DXMatrixIdentity(&g_Wall[i].mtxWorld);

		//大きさの反映
		D3DXMatrixScaling(&mtxScale, g_Wall[i].scale.x, g_Wall[i].scale.y, g_Wall[i].scale.z);
		D3DXMatrixMultiply(&g_Wall[i].mtxWorld, &g_Wall[i].mtxWorld, &mtxScale);

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[i].rot.y, g_Wall[i].rot.x, g_Wall[i].rot.z);
		D3DXMatrixMultiply(&g_Wall[i].mtxWorld, &g_Wall[i].mtxWorld, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, g_Wall[i].pos.x, g_Wall[i].pos.y, g_Wall[i].pos.z);
		D3DXMatrixMultiply(&g_Wall[i].mtxWorld, &g_Wall[i].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Wall[i].mtxWorld);

		//現在のマテリアル取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Wall[i].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Wall[i].dwNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			//テクスチャ
			pDevice->SetTexture(0, g_Wall[i].apTexture[nCntMat]);

			//モデル描画
			g_Wall[i].pMesh->DrawSubset(nCntMat);
		}

		pDevice->SetMaterial(&matDef);
	}
}