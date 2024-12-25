//---------------------------------------
//
//サンタの処理[enemy_santa.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _ENEMY_SANTA_H_
#define _ENEMY_SANTA_H_


#include"main.h"
#include"stage.h"
#include"model.h"

#define SANTA_BODY_NAME "data\\MODEL\\AKRmodel\\00_body.x"
#define SANTA_HEAD_NAME "data\\MODEL\\AKRmodel\\01_head.x"
#define SANTA_RIGHTARM_NAME "data\\MODEL\\AKRmodel\\02_armR.x"
#define SANTA_RIGHTHAND_NAME "data\\MODEL\\AKRmodel\\03_handR.x"
#define SANTA_LEFTARM_NAME "data\\MODEL\\AKRmodel\\04_armL.x"
#define SANTA_LEFTHAND_NAME "data\\MODEL\\AKRmodel\\05_handL.x"
#define SANTA_RIGHTLEG_NAME "data\\MODEL\\AKRmodel\\06_legR.x"
#define SANTA_RIGHTFOOT_NAME "data\\MODEL\\AKRmodel\\07_footR.x"
#define SANTA_LEFTLEG_NAME "data\\MODEL\\AKRmodel\\08_legL.x"
#define SANTA_LEFTFOOT_NAME "data\\MODEL\\AKRmodel\\09_footL.x"
#define MAX_MODEL (16)
#define NUM_MODEL (10)
#define MAX_KEY (16)
#define NUM_KEY (2)
#define MAX_MOTION (16)
#define NUM_MOTION (1)
#define SPEED (1.0f)
#define SPEED_DEF (0.0f)
#define JUMP (20.0f)
#define JUMP_INA (0.9f)
#define SANTA_INA (0.1f)
#define ROT_SPEED (0.1f)
#define SCALE_SPEED (0.2f)
#define SCALE_MIN (0.5f)
#define SCALE_MAX (10.0f)
#define SANTA_LIFE (1000)
#define BLEND_FRAME (10.0f)
#define SANTA_SIZE (50.0f)

//プレイヤー状態の列挙型定義
typedef enum
{
	SANTASTATE_APPEAR = 0,//待機状態
	SANTASTATE_NORMAL,//出現状態
	SANTASTATE_DAMAGE,//ダメージ
	SANTASTATE_DIE,//死
	SANTASTATE_MAX//数
}SANTASTATE;

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_MOVE,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,
	MOTIONTYPE_MAX
}MOTIONTYPE;

//キーの構造体
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;
	KEY aKey[MAX_MODEL];
}KEY_INFO;

typedef struct
{
	bool bLoop;
	int nNumKey;
	KEY_INFO aKeyInfo[MAX_KEY];
}MOTION_INFO;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 scale;
	bool bJump;
	int nLife;
	SANTASTATE state;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
	int nIdxLife;
	Model aModel[MAX_MODEL];
	int nNumModel;
	MOTION_INFO aMotionInfo[MAX_MOTION];
	int nNumMotion;
	MOTIONTYPE motionType;
	bool bLoopMotion;
	int nNumKey;
	int nKey;
	int nCounterMotion;
	Stage* pStage;
	bool bUse;
}Enemy;

void InitEnemy(void);//ポリゴンの初期化処理
void UninitEnemy(void);//ポリゴンの終了処理
void UpdateEnemy(void);//ポリゴンの更新処理
void DrawEnemy(void);//ポリゴンの描画処理
Enemy* GetEnemy(void);

void UpdateMotionEnemy(void);
void CollisionEnemy(D3DXVECTOR3 pos, float Length);

#endif _ENEMY_SANTA_H_