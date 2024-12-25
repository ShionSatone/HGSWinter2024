//---------------------------------------
//
//窓処理[window.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _WINDOW_H_
#define _WINDOW_H_

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
	int nIdxWindowParent;
}Window;

void InitWindow(void);//ポリゴンの初期化処理
void UninitWindow(void);//ポリゴンの終了処理
void UpdateWindow(void);//ポリゴンの更新処理
void DrawWindow(void);//ポリゴンの描画処理

Window* GetWindow(void);
void SetWindowPos(D3DXVECTOR3 pos);
#endif _BED_H_