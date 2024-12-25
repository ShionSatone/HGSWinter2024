//---------------------------------------
//
//カメラの定義・宣言[camera.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

#define CAMERA_WIDTH (90.0f)//視野の広さ
#define CAMERA_MIN (10.0f)//視野の最小
#define CAMERA_MAX (20000.0f)//視野の最大

//カメラ構造体
typedef struct
{
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	D3DXVECTOR3 posU;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
}Camera;

void InitCamera(void);//初期化処理
void UninitCamera(void);//終了処理
void UpdateCamera(void);//更新処理
void SetCamera(void);//描画処理
Camera* GetCamera(void);

#endif _CAMERA_H_