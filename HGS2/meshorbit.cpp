//=================================
//
// 剣の軌跡 [meshorbit.h]
// Author:YOSHIDA YUUTO
//
//=================================

//****************************
//インクルードファイル
//****************************
#include"meshorbit.h"
#include "input.h"
#include "player.h"

//****************************
//マクロ定義
//****************************
#define MAX_ORBIT (64) //頂点数

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_pTextureMeshSword = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSword = NULL; //頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshSword = NULL;//インデックスバッファへのポインタ
MESHSOAD g_MeshSword;

//===============================
//メッシュフィールドの初期化処理
//===============================
void InitMeshSword(void)
{
	int nCnt = 0;

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();//デバイスを取得

		//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\orbit.png",
		&g_pTextureMeshSword);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_ORBIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSword,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_ORBIT,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshSword,
		NULL);

	g_MeshSword.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshSword.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshSword.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_MeshSword.Scal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshSword->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点座標の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点座標の設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffMeshSword->Unlock();

	WORD* pIdx;

	//インデックスバッファのロック
	g_pIdxBuffMeshSword->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MAX_ORBIT; nCnt++)
	{
		pIdx[nCnt] = nCnt;
	}
	//インデックスバッファのアンロック
	g_pIdxBuffMeshSword->Unlock();

}

//===============================
//メッシュフィールドの終了処理
//===============================ccc
void UninitMeshSword(void)
{
	//テクスチャの解放
	if (g_pTextureMeshSword != NULL)
	{
		g_pTextureMeshSword->Release();
		g_pTextureMeshSword = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffMeshSword != NULL)
	{
		g_pVtxBuffMeshSword->Release();
		g_pVtxBuffMeshSword = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffMeshSword != NULL)
	{
		g_pIdxBuffMeshSword->Release();
		g_pIdxBuffMeshSword = NULL;
	}
}

//===============================
//メッシュフィールドの更新処理
//===============================
void UpdateMeshSword(void)
{

	Player* pPlayer = GetPlayer();  // プレイヤー情報を取得
	VERTEX_3D* pVtx;

	int vtxCnt = 0;

	// 頂点バッファをロック
	g_pVtxBuffMeshSword->Lock(0, 0, (void**)&pVtx, 0);

	if (pPlayer->motionType == MOTIONTYPE_ACTION)
	{
		for (int nCnt = 2; nCnt < MAX_ORBIT; nCnt += 2, vtxCnt += 2)
		{
			pVtx[nCnt].pos.x = pVtx[vtxCnt].pos.x;
			pVtx[nCnt].pos.y = pVtx[vtxCnt].pos.y;
			pVtx[nCnt].pos.z = pVtx[vtxCnt].pos.z;

			pVtx[nCnt + 1].pos.x = pVtx[vtxCnt + 1].pos.x;
			pVtx[nCnt + 1].pos.y = pVtx[vtxCnt + 1].pos.y;
			pVtx[nCnt + 1].pos.z = pVtx[vtxCnt + 1].pos.z;
		}
		pVtx[0].pos.x = pPlayer->SwordMtxWorld._41;
		pVtx[0].pos.y = pPlayer->SwordMtxWorld._42;
		pVtx[0].pos.z = pPlayer->SwordMtxWorld._43;

		pVtx[1].pos.x = pPlayer->aModel[MODEL_SWORD].mtxWorld._41;
		pVtx[1].pos.y = pPlayer->aModel[MODEL_SWORD].mtxWorld._42;
		pVtx[1].pos.z = pPlayer->aModel[MODEL_SWORD].mtxWorld._43;

	}

	// 頂点バッファをアンロック
	g_pVtxBuffMeshSword->Unlock();
}

//===============================
//メッシュフィールドの描画処理
//===============================
void DrawMeshSword(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	Player* pPlayer = GetPlayer();  // プレイヤー情報を取得

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	if (pPlayer->motionType == MOTIONTYPE_ACTION)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_MeshSword.mtxWorldMeshSword);

		pDevice->SetRenderState(D3DRS_CULLMODE, TRUE);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshSword.rot.y, g_MeshSword.rot.x, g_MeshSword.rot.z);
		D3DXMatrixMultiply(&g_MeshSword.mtxWorldMeshSword, &g_MeshSword.mtxWorldMeshSword, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_MeshSword.pos.x, g_MeshSword.pos.y, g_MeshSword.pos.z);
		D3DXMatrixMultiply(&g_MeshSword.mtxWorldMeshSword, &g_MeshSword.mtxWorldMeshSword, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshSword.mtxWorldMeshSword);

		//頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMeshSword, 0, sizeof(VERTEX_3D));

		//インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffMeshSword);

		//テクスチャフォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshSword);

		//ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_ORBIT, 0, 1);
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
