//---------------------------------------
//
//�p�[�e�B�N���\�������̒�`�E�錾[particle.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include"main.h"

#define MAX_PARTICLE (128)//�ő吔
#define PARTICLE_NUM (15)//�t���[��������
#define PARTICLE_LIFE (100)//�c���

// �p�[�e�B�N���̎��
typedef enum
{
	PARTICLE_TYPE_NONE = 0,
	PARTICLE_TYPE_COLLECT,			// ���
	PARTICLE_TYPE_COLLECT_CMP,		// �������
	PARTICLE_TYPE_MAX
}PARTICLE_TYPE;

//�e�\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 scale;//�X�P�[��
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
	PARTICLE_TYPE type;
}PARTICLE;

void InitParticle(void);//�p�[�e�B�N���̏���������
void UninitParticle(void);//�p�[�e�B�N���̏I������
void UpdateParticle(void);//�p�[�e�B�N���̍X�V����
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 scale, PARTICLE_TYPE type);//�p�[�e�B�N���ݒ�

D3DXCOLOR ParticleBullet(int nIdx, D3DXVECTOR3& pos, D3DXVECTOR3& move, D3DXCOLOR col, D3DXVECTOR3& scale, int& nLife);
D3DXCOLOR ParticleCompletion(int nIdx, D3DXVECTOR3& pos, D3DXVECTOR3& move, D3DXCOLOR col, D3DXVECTOR3& scale, int& nLife);

#endif _PARTICLE_H_