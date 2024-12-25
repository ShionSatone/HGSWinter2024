//---------------------------------------
//
//壁処理[wall.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _WALL_H_
#define _WALL_H_

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
	int nIdxWallParent;
}Wall;

void InitWall(void);//ポリゴンの初期化処理
void UninitWall(void);//ポリゴンの終了処理
void UpdateWall(void);//ポリゴンの更新処理
void DrawWall(void);//ポリゴンの描画処理

Wall* GetWall(void);
void SetWallPos(D3DXVECTOR3 pos);

#endif _BED_H_