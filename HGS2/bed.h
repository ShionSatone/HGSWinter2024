//---------------------------------------
//
//ベッド処理[present.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _BED_H_
#define _BED_H_

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
	int nIdxBedParent;
	D3DXVECTOR3 Size;//ベッドのサイズ
}Bed;

void InitBed(void);//ポリゴンの初期化処理
void UninitBed(void);//ポリゴンの終了処理
void UpdateBed(void);//ポリゴンの更新処理
void DrawBed(void);//ポリゴンの描画処理

Bed* GetBed(void);
void SetBedPos(D3DXVECTOR3 pos);
#endif _BED_H_