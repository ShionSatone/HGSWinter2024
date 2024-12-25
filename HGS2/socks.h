//---------------------------------------
//
//�x�b�h����[present.h]
//Author fuma sato
//
//---------------------------------------

#if 0
#ifndef _BED_H_
#define _BED_H_

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
	int nIdxBedParent;
}Bed;

void InitBed(void);//�|���S���̏���������
void UninitBed(void);//�|���S���̏I������
void UpdateBed(void);//�|���S���̍X�V����
void DrawBed(void);//�|���S���̕`�揈��

Bed* GetBed(void);
void SetBedPos(D3DXVECTOR3 pos);
#endif
#endif _BED_H_