//---------------------------------------
//
//スコア処理の定義・宣言[score.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"

#define SCORE_MAX (10)//桁数
#define U_MAX_S (11)//テクスチャ数(横)
#define V_MAX_S (1)//テクスチャ数(縦)
#define SCORE_WIDTH (350.0f)//サイズ
#define SCORE_HEIGHT (70.0f)//サイズ
#define DIGIT (10)//進数

//プロトタイプ宣言
void InitScore(void);//スコアの初期化処理
void UninitScore(void);//スコアの終了処理
void UpdateScore(void);//スコアの更新処理
void DrawScore(void);//スコアの描画処理
void SetScore(int nScore,bool bTex);//スコア書き換え
void AddScore(int nValue);//スコア加算
int GetScore(void);//スコア取得
int Digit(int nData, int nDigit);//分割処理

#endif _SCORE_H_
