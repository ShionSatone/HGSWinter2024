//---------------------------------------
//
//モデル表示処理の定義・宣言[blacksanta.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _BLACKSANTA_H_
#define _BLACKSANTA_H_
#include"main.h"
#include"player.h"
#include"model.h"

#define BLACKSANTA_BODY_NAME "data\\MODEL\\AKRmodel\\00_body.x"
#define MAX_MODEL_BLACKSANTA (16)
#define NUM_MODEL_BLACKSANTA (1)
#define MAX_KEY_BLACKSANTA (16)
#define NUM_KEY_BLACKSANTA (2)
#define MAX_MOTION_BLACKSANTA (16)
#define NUM_MOTION_BLACKSANTA (1)
#define BLACKSANTA_SPEED (1.0f)
#define BLACKSANTA_SPEED_DEF (0.0f)
#define BLACKSANTA_INA (0.1f)
#define BLACKSANTA_ROT_SPEED (0.1f)
#define BLACKSANTA_SCALE_SPEED (0.2f)
#define BLACKSANTA_SCALE_MIN (0.5f)
#define BLACKSANTA_SCALE_MAX (10.0f)
#define BLACKSANTA_LIFE (1000)
#define BLACKSANTA_BLEND_FRAME (10.0f)
#define BLACKSANTA_SIZE (50.0f)

//プレイヤー状態の列挙型定義
typedef enum
{
	BLACKSANTASTATE_APPEAR = 0,//復活状態
	BLACKSANTASTATE_NORMAL,//通常
	BLACKSANTASTATE_DAMAGE,//ダメージ
	BLACKSANTASTATE_DIE,//死
	BLACKSANTASTATE_MAX//数
}BLACKSANTASTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 scale;
	int nLife;
	BLACKSANTASTATE state;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
	int nIdxLife;
	Model aModel[MAX_MODEL_BLACKSANTA];
	int nNumModel;
	MOTION_INFO aMotionInfo[MAX_MOTION_BLACKSANTA];
	int nNumMotion;
	MOTIONTYPE motionType;
	bool bLoopMotion;
	int nNumKey;
	int nKey;
	int nCounterMotion;
	Stage* pStage;
	bool bUse;
}BlackSanta;

void InitBlackSanta(void);//ポリゴンの初期化処理
void UninitBlackSanta(void);//ポリゴンの終了処理
void UpdateBlackSanta(void);//ポリゴンの更新処理
void DrawBlackSanta(void);//ポリゴンの描画処理
BlackSanta* GetBlackSanta(void);

void SetBlackSanta(D3DXVECTOR3 pos);
void EndBlackSanta(void);

void UpdateBlackSantaMotion(void);
void CollisionBlackSanta(D3DXVECTOR3 pos, float Length);
#endif