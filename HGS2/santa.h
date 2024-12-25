//---------------------------------------
//
//モデル表示処理の定義・宣言[santa.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SANTA_H_
#define _SANTA_H_
#include"main.h"
#include"player.h"
#include"model.h"

#define SANTA_BODY_NAME "data\\MODEL\\AKRmodel\\00_body.x"
#define MAX_MODEL_SANTA (16)
#define NUM_MODEL_SANTA (1)
#define MAX_KEY_SANTA (16)
#define NUM_KEY_SANTA (2)
#define MAX_MOTION_SANTA (16)
#define NUM_MOTION_SANTA (1)
#define SANTA_SPEED (1.0f)
#define SANTA_SPEED_DEF (0.0f)
#define SANTA_INA (0.1f)
#define SANTA_ROT_SPEED (0.1f)
#define SANTA_SCALE_SPEED (0.2f)
#define SANTA_SCALE_MIN (0.5f)
#define SANTA_SCALE_MAX (10.0f)
#define SANTA_LIFE (1000)
#define SANTA_BLEND_FRAME (10.0f)
#define SANTA_SIZE (50.0f)
#define PRESENT_SPACE (1.0f)

//プレイヤー状態の列挙型定義
typedef enum
{
	SANTASTATE_APPEAR = 0,//復活状態
	SANTASTATE_NORMAL,//通常
	SANTASTATE_DAMAGE,//ダメージ
	SANTASTATE_DIE,//死
	SANTASTATE_MAX//数
}SANTASTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 Startpos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 scale;
	int nLife;
	SANTASTATE state;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
	int nIdxLife;
	Model aModel[MAX_MODEL_SANTA];
	int nNumModel;
	MOTION_INFO aMotionInfo[MAX_MOTION_SANTA];
	int nNumMotion;
	MOTIONTYPE motionType;
	bool bLoopMotion;
	int nNumKey;
	int nKey;
	int nCounterMotion;
	Stage* pStage;
	bool bPresent;
	bool bUse;
}Santa;

void InitSanta(void);//ポリゴンの初期化処理
void UninitSanta(void);//ポリゴンの終了処理
void UpdateSanta(void);//ポリゴンの更新処理
void DrawSanta(void);//ポリゴンの描画処理
Santa* GetSanta(void);

void SetSanta(D3DXVECTOR3 pos);
void EndSanta(void);

void UpdateSantaMotion(void);
void CollisionSanta(D3DXVECTOR3 pos, float Length);
#endif