//---------------------------------------
//
//チュートリアル処理の定義・宣言[tuto.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _TUTO_H_
#define _TUTO_H_

#include"main.h"

#define TEXTURE_TUTO "data\\TEXTURE\\tutorial.png"

//プロトタイプ宣言
void InitTuto(void);//スコアの初期化処理
void UninitTuto(void);//スコアの終了処理
void UpdateTuto(void);//スコアの更新処理
void DrawTuto(void);//スコアの描画処理

#endif _TUTO_H_
