//---------------------------------------
//
//モデル表示処理の定義・宣言[player.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"
#include"stage.h"
#include"model.h"

#define PLAYER_BODY_NAME "data\\MODEL\\AKRmodel\\00_body.x"
#define PLAYER_HEAD_NAME "data\\MODEL\\AKRmodel\\01_head.x"
#define PLAYER_RIGHTARM_NAME "data\\MODEL\\AKRmodel\\02_armR.x"
#define PLAYER_RIGHTHAND_NAME "data\\MODEL\\AKRmodel\\03_handR.x"
#define PLAYER_LEFTARM_NAME "data\\MODEL\\AKRmodel\\04_armL.x"
#define PLAYER_LEFTHAND_NAME "data\\MODEL\\AKRmodel\\05_handL.x"
#define PLAYER_RIGHTLEG_NAME "data\\MODEL\\AKRmodel\\06_legR.x"
#define PLAYER_RIGHTFOOT_NAME "data\\MODEL\\AKRmodel\\07_footR.x"
#define PLAYER_LEFTLEG_NAME "data\\MODEL\\AKRmodel\\08_legL.x"
#define PLAYER_LEFTFOOT_NAME "data\\MODEL\\AKRmodel\\09_footL.x"
#define LOADPLAYER ("data\\MOTION\\model15p.txt")
#define MAX_MODEL (16)
#define NUM_MODEL (10)
#define MAX_KEY (16)
#define NUM_KEY (2)
#define MAX_MOTION (16)
#define NUM_MOTION (1)
#define SPEED (2.8f)
#define SPEED_DEF (0.0f)
#define JUMP (20.0f)
#define JUMP_INA (0.9f)
#define PLAYER_INA (0.5f)
#define ROT_SPEED (0.1f)
#define SCALE_SPEED (0.2f)
#define SCALE_MIN (0.5f)
#define SCALE_MAX (10.0f)
#define PLAYER_LIFE (1000)
#define BLEND_FRAME (10.0f)
#define PLAYER_SIZE (50.0f)
#define MODEL_SWORD (15) // 剣のモデルのインデックス

//プレイヤー状態の列挙型定義
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//復活状態
	PLAYERSTATE_NORMAL,//通常
	PLAYERSTATE_DAMAGE,//ダメージ
	PLAYERSTATE_DIE,//死
	PLAYERSTATE_SLEEP,//睡眠
	PLAYERSTATE_MAX//数
}PLAYERSTATE;

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

//************************
// モーションの状態
//************************
typedef enum
{
	MOTIONSTATE_NEUTRAL = 0,//ニュートラル
	MOTIONSTATE_MOVE,       //歩きモーション
	MOTIONSTATE_ACTION,     //攻撃モーション
	MOTIONSTATE_MAX
}MOTIONSTATE;

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
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 scale;
	bool bJump;
	int nLife;
	PLAYERSTATE state;
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
	MOTIONSTATE motionstate; // モーションの状態
	float PlayerMove;//プレイヤーの移動量
	int nCounterstate; // プレイヤーの状態カウンター
	D3DXVECTOR3 SwordOffpos;//剣の架空の位置の基準
	D3DXMATRIX SwordMtxWorld;//剣の先のワールドマトリックス
	D3DXVECTOR3 Size;//プレイヤーのサイズ
}Player;

void InitPlayer(void);//ポリゴンの初期化処理
void UninitPlayer(void);//ポリゴンの終了処理
void UpdatePlayer(void);//ポリゴンの更新処理
void DrawPlayer(void);//ポリゴンの描画処理
void SetWorldMtx(void);//剣のワールドマトリックス設定用関数
Player* GetPlayer(void);
bool CollisionSword(D3DXVECTOR3 pos);//サンタと剣の当たり判定
void CollisionObj(D3DXVECTOR3 pos, D3DXVECTOR3 Size);

void UpdateMotion(void);
void CollisionPlayer(D3DXVECTOR3 pos, float Length);
void LoadPlayer(void);//プレイヤーの読み込み処理
#endif _PLAYER_H_