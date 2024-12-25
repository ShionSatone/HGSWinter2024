//---------------------------------------
//
//パーティクル表示処理の定義・宣言[particle.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include"main.h"

#define MAX_PARTICLE (128)//最大数
#define PARTICLE_NUM (15)//フレーム発生数
#define PARTICLE_LIFE (100)//残留具合

// パーティクルの種類
typedef enum
{
	PARTICLE_TYPE_NONE = 0,
	PARTICLE_TYPE_COLLECT,			// 回収
	PARTICLE_TYPE_COLLECT_CMP,		// 回収完了
	PARTICLE_TYPE_MAX
}PARTICLE_TYPE;

//弾構造体
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 scale;//スケール
	int nLife;//寿命
	bool bUse;//使用しているかどうか
	PARTICLE_TYPE type;
}PARTICLE;

void InitParticle(void);//パーティクルの初期化処理
void UninitParticle(void);//パーティクルの終了処理
void UpdateParticle(void);//パーティクルの更新処理
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 scale, PARTICLE_TYPE type);//パーティクル設定

D3DXCOLOR ParticleBullet(int nIdx, D3DXVECTOR3& pos, D3DXVECTOR3& move, D3DXCOLOR col, D3DXVECTOR3& scale, int& nLife);
D3DXCOLOR ParticleCompletion(int nIdx, D3DXVECTOR3& pos, D3DXVECTOR3& move, D3DXCOLOR col, D3DXVECTOR3& scale, int& nLife);

#endif _PARTICLE_H_