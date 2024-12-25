//---------------------------------------
//
//�v���[���g����[present.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _PRESENT_H_
#define _PRESENT_H_

#include"main.h"

typedef struct
{
	LPD3DXMESH pMesh;//���_���|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���|�C���^
	LPDIRECT3DTEXTURE9 apTexture[64];
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posDef;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	D3DXMATRIX mtxWorld;
	DWORD dwNumMat;//�}�e���A����
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMinDef;
	D3DXVECTOR3 vtxMaxDef;
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxPresentParent;
	int nIdxShadow;
}Present;

void InitPresent(void);//�|���S���̏���������
void UninitPresent(void);//�|���S���̏I������
void UpdatePresent(void);//�|���S���̍X�V����
void DrawPresent(void);//�|���S���̕`�揈��

Present* GetPresent(void);
void SetPresentPos(D3DXVECTOR3 pos);

#endif _MODEL_H_