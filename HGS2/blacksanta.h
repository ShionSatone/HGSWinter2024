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

#define BLACKSANTA_BODY_NAME "data\\MODEL\\BlackSantamodel\\00_blacksantabody.x"
#define BLACKSANTA_HEAD_NAME "data\\MODEL\\BlackSantamodel\\01_blacksantahead.x"
#define BLACKSANTA_RIGHTARM_NAME "data\\MODEL\\BlackSantamodel\\02_blacksantaarmR.x"
#define BLACKSANTA_RIGHTHAND_NAME "data\\MODEL\\BlackSantamodel\\03_blacksantahandR.x"
#define BLACKSANTA_LEFTARM_NAME "data\\MODEL\\BlackSantamodel\\04_blacksantaarmL.x"
#define BLACKSANTA_LEFTHAND_NAME "data\\MODEL\\BlackSantamodel\\05_blacksantahandL.x"
#define BLACKSANTA_RIGHTLEG_NAME "data\\MODEL\\BlackSantamodel\\06_blacksantalegR.x"
#define BLACKSANTA_RIGHTFOOT_NAME "data\\MODEL\\BlackSantamodel\\07_blacksantafootR.x"
#define BLACKSANTA_LEFTLEG_NAME "data\\MODEL\\BlackSantamodel\\08_blacksantalegL.x"
#define BLACKSANTA_LEFTFOOT_NAME "data\\MODEL\\BlackSantamodel\\09_blacksantafootL.x"
#define MAX_MODEL_BLACKSANTA (16)
#define NUM_MODEL_BLACKSANTA (10)
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
#define BLACKSANTA_BLEND_FRAME (10.0f)
#define BLACKSANTA_SIZE (50.0f)
#define STEAL1_TIME (3)
#define STEAL2_TIME (5)
#define STEAL3_TIME (10)

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
	BLACKSANTASTATE state;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
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
	int nStealCnt;
	int nStealTime;
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