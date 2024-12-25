//---------------------------------------
//
//プレゼント処理[present.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _PRESENT_H_
#define _PRESENT_H_

#include"main.h"

typedef struct
{
	LPD3DXMESH pMesh;//頂点情報ポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルポインタ
	LPDIRECT3DTEXTURE9 apTexture[64];
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posDef;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	D3DXMATRIX mtxWorld;
	DWORD dwNumMat;//マテリアル数
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMinDef;
	D3DXVECTOR3 vtxMaxDef;
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxPresentParent;
	int nIdxShadow;
}Present;

void InitPresent(void);//ポリゴンの初期化処理
void UninitPresent(void);//ポリゴンの終了処理
void UpdatePresent(void);//ポリゴンの更新処理
void DrawPresent(void);//ポリゴンの描画処理

Present* GetPresent(void);
void SetPresentPos(D3DXVECTOR3 pos);

#endif _MODEL_H_