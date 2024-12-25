//=======================================
//
//　ドア [door.h]
//　Author YOSHIDA YUTO
//
//=======================================

#ifndef _DOOR_H_
#define _DOOR_H_

//***************************************
// インクルードファイル
//***************************************
#include"main.h"

//***************************************
// マクロ定義
//***************************************
#define MAX_TEXTURE (64) // テクスチャの最大数

//***************************************
// ドアの構造体
//***************************************
typedef struct
{
	LPD3DXMESH pMesh;//頂点情報ポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルポインタ
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTURE];//テクスチャへのポインタ
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 rotDest;//目的の向き
	D3DXVECTOR3 scale;//大きさ
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	DWORD dwNumMat;//マテリアル数
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxBedParent;
}Door;

//***************************************
// プロトタイプ宣言
//***************************************
void InitDoor(void);//ドアの初期化処理
void UninitDoor(void);//ドアのの終了処理
void UpdateDoor(void);//ドアのの更新処理
void DrawDoor(void);//ドアのの描画処理
Door* GetDoor(void);//ドアの取得処理
void SetDoorPos(D3DXVECTOR3 pos);//ドアの設定処理
#endif _DOOR_H_
