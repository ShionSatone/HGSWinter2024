//=======================================
//
//　煙突 [chimney.h]
//　Author YOSHIDA YUTO
//
//=======================================

#ifndef _CHIMNEY_H_
#define _CHIMNEY_H_

//***************************************
// インクルードファイル
//***************************************
#include"main.h"

//***************************************
// マクロ定義
//***************************************
#define MAX_TEXTURE (64) // テクスチャの最大数

//***************************************
// 煙突の構造体
//***************************************
typedef struct
{
	LPD3DXMESH pMesh;//頂点情報ポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルポインタ
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTURE];//テクスチャへのポインタ
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 scale;//大きさ
	D3DXVECTOR3 vtxMax,vtxMin,Size;//大きさ
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	DWORD dwNumMat;//マテリアル数
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxBedParent;
}Chimney;

//***************************************
// プロトタイプ宣言
//***************************************
void InitChimney(void);//煙突の初期化処理
void UninitChimney(void);//煙突のの終了処理
void UpdateChimney(void);//煙突のの更新処理
void DrawChimney(void);//煙突のの描画処理
Chimney* GetChimney(void);//煙突の取得処理
void SetChimneyPos(D3DXVECTOR3 pos);//煙突の設定処理
#endif _CHIMNEY_H_
