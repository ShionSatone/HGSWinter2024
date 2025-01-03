//---------------------------------------
//
//靴下処理[socks.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _SOCKS_H_
#define _SOCKS_H_

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
	D3DXVECTOR3 vtxMax, vtxMin,Size;
	D3DXMATRIX mtxWorld;
	DWORD dwNumMat;//マテリアル数
	D3DXVECTOR3 vtxMinDef;
	D3DXVECTOR3 vtxMaxDef;
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxSocksParent;
}Socks;

void InitSocks(void);//ポリゴンの初期化処理
void UninitSocks(void);//ポリゴンの終了処理
void UpdateSocks(void);//ポリゴンの更新処理
void DrawSocks(void);//ポリゴンの描画処理

Socks* GetSocks(void);
void SetSocksPos(D3DXVECTOR3 pos);
#endif _BED_H_