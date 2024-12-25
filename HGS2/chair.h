//=======================================
//
//　椅子 [chair.h]
//　Author YOSHIDA YUTO
//
//=======================================

#ifndef _CHAIR_H_
#define _CHAIR_H_

//***************************************
// インクルードファイル
//***************************************
#include"main.h"

//***************************************
// マクロ定義
//***************************************
#define MAX_TEXTURE (64) // テクスチャの最大数

//***************************************
// 椅子の構造体
//***************************************
typedef struct
{
	LPD3DXMESH pMesh;//頂点情報ポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルポインタ
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTURE];//テクスチャへのポインタ
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 scale;//大きさ
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	DWORD dwNumMat;//マテリアル数
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxBedParent;
}Chair;

//***************************************
// プロトタイプ宣言
//***************************************
void InitChair(void);//椅子の初期化処理
void UninitChair(void);//椅子のの終了処理
void UpdateChair(void);//椅子のの更新処理
void DrawChair(void);//椅子のの描画処理
Chair* GetChair(void);//椅子の取得処理
void SetChairPos(D3DXVECTOR3 pos);//椅子の設定処理
#endif _CHAIR_H_
