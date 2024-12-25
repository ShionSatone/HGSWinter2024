//=======================================
//
//　机 [desk.h]
//　Author YOSHIDA YUTO
//
//=======================================

#ifndef _DESK_H_
#define _DESK_H_

//***************************************
// インクルードファイル
//***************************************
#include"main.h"

//***************************************
// マクロ定義
//***************************************
#define MAX_TEXTURE (64) // テクスチャの最大数

//***************************************
// 机の構造体
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
}Desk;

//***************************************
// プロトタイプ宣言
//***************************************
void InitDesk(void);//机の初期化処理
void UninitDesk(void);//机のの終了処理
void UpdateDesk(void);//机のの更新処理
void DrawDesk(void);//机のの描画処理
Desk* GetDesk(void);//机の取得処理
void SetDeskPos(D3DXVECTOR3 pos);//机の設定処理
#endif _DESK_H_
