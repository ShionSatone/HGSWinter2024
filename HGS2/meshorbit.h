//=================================
//
// 剣の軌跡 [meshorbit.h]
// Author:YOSHIDA YUUTO
//
//=================================

#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

//****************************
//インクルードファイル
//****************************
#include"main.h"

//****************************
//マクロ定義
//****************************
#define SOAD_WIDTH (10.0f) //横幅
#define SOAD_HEIGHT (10.0f) //高さ

//#define XVTX (50) //Xの値
//#define ZVTX (50) //yの値

#define SOAD_VERTEX (20) //頂点数
//#define INDEX (POLYGON + 2)  //インデックス
//#define POLYGON (((XVTX * ZVTX) * 2)) + (4 * (ZVTX - 1)) //ポリゴン数

//****************************
//剣の軌道の構造体
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//剣の軌道の位置
	D3DXVECTOR3 rot;//剣の軌道の向き
	D3DXCOLOR col;//色
	D3DXMATRIX mtxWorldMeshSword;//剣の軌道のワールドマトリックス
	D3DXVECTOR3 Scal;
}MESHSOAD;

//****************************
//プロトタイプ宣言
//****************************
void InitMeshSword(void);//剣の軌道の初期化処理
void UninitMeshSword(void);//剣の軌道の終了処理
void UpdateMeshSword(void);//剣の軌道の更新処理
void DrawMeshSword(void);//剣の軌道の描画処理
#endif