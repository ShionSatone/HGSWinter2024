//---------------------------------------
//
//弾表示処理[particle.cpp]
//Author fuma sato
//
//---------------------------------------

#include"particle.h"
#include"player.h"
#include"effect.h"

//グローバル
PARTICLE g_aParticle[MAX_PARTICLE];//弾の情報
//-----------------
//弾の初期化処理
//-----------------
void InitParticle(void)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		g_aParticle[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[i].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aParticle[i].nLife = PARTICLE_LIFE;
		g_aParticle[i].bUse = false;//使用していない状態にする
		g_aParticle[i].type = PARTICLE_TYPE_NONE;
	}
}

//----------------
//弾の終了処理
//----------------
void UninitParticle(void)
{

}

//----------------
//弾の更新処理
//----------------
void UpdateParticle(void)
{
	EFFECT_TYPE EfectType;

	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (g_aParticle[i].bUse == true)
		{//弾が使用されている

			for (int i2 = 0; i2 < PARTICLE_NUM; i2++)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), move = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				int nLife = 0;

				col = ParticleBullet(i, pos, move, col, scale, nLife);

				SetEffect(pos, move, col, scale, nLife, EFFECT_TYPE_NORMAL);
			}

			g_aParticle[i].nLife--;
			g_aParticle[i].scale *= ((float)g_aParticle[i].nLife) / ((float)PARTICLE_LIFE);

			if (g_aParticle[i].nLife <= 0)
			{
				g_aParticle[i].bUse = false;
			}
		}
	}
}

//-------------------
//発通常弾
//-------------------
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 scale, PARTICLE_TYPE type)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (g_aParticle[i].bUse == false)
		{//弾が使用されていない
			g_aParticle[i].pos = pos;
			g_aParticle[i].scale = scale;
			g_aParticle[i].nLife = PARTICLE_LIFE;
			g_aParticle[i].bUse = true;
			g_aParticle[i].type = type;
			break;
		}
	}
}

//-------------------
// 弾
//-------------------
D3DXCOLOR ParticleBullet(int nIdx, D3DXVECTOR3& pos, D3DXVECTOR3& move, D3DXCOLOR col, D3DXVECTOR3& scale, int& nLife)
{
	D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fangle = 0.0f, fspeed = 0.0f, fscale = 0.0f, length = 0.0f;

	pos = g_aParticle[nIdx].pos;
	fangle = (float)(rand() % 629 - 314) / 100.0f;
	fspeed = (float)(rand() % 2) / 10.0f + 1.0f;
	dir.x = (float)(rand() % 201 - 100) / 100.0f;
	dir.y = (float)(rand() % 201 - 100) / 100.0f;
	dir.z = (float)(rand() % 201 - 100) / 100.0f;
	length = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	dir.x /= length;
	dir.y /= length;
	dir.z /= length;
	move.x = dir.x * fspeed;
	move.y = dir.y * fspeed;
	move.z = dir.z * fspeed;
	col = D3DXCOLOR((float)(rand() % 101) / 100.0f, (float)(rand() % 101) / 100.0f, (float)(rand() % 101) / 100.0f, (float)(rand() % 51) / 100.0f);
	fscale = (float)(rand() % (int)(g_aParticle[nIdx].scale.x + 1.0f) * 1.0f);
	scale.x = fscale;
	scale.y = fscale;
	scale.z = fscale;
	nLife = g_aParticle[nIdx].nLife;

	return col;
}

//-------------------
// 回収完了
//-------------------
D3DXCOLOR ParticleCompletion(int nIdx, D3DXVECTOR3& pos, D3DXVECTOR3& move, D3DXCOLOR col, D3DXVECTOR3& scale, int& nLife)
{
	D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fangle = 0.0f, fspeed = 0.0f, fscale = 0.0f, length = 0.0f;

	pos = g_aParticle[nIdx].pos;
	fangle = (float)(rand() % 629 - 314) / 100.0f;
	fspeed = (float)(rand() % 100) / 10.0f + 1.0f;
	dir.x = (float)(rand() % 201 - 100) / 100.0f;
	dir.y = (float)(rand() % 201 - 100) / 100.0f;
	dir.z = (float)(rand() % 201 - 100) / 100.0f;
	length = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	dir.x /= length;
	dir.y /= length;
	dir.z /= length;
	move.x = dir.x * fspeed;
	move.y = dir.y * fspeed;
	move.z = dir.z * fspeed;
	col = D3DXCOLOR((float)(rand() % 101) / 100.0f, (float)(rand() % 101) / 100.0f, (float)(rand() % 101) / 100.0f, (float)(rand() % 51) / 100.0f);
	fscale = (float)(rand() % (int)(g_aParticle[nIdx].scale.x + 1.0f) * 10.0f);
	scale.x = fscale;
	scale.y = fscale;
	scale.z = fscale;
	nLife = g_aParticle[nIdx].nLife;

	return col;
}