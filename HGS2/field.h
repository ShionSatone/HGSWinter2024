//---------------------------------------
//
//�x�b�h����[present.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _FIELD_H_
#define _FIELD_H_

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
	int nIdxFieldParent;
	D3DXVECTOR3 Size;//�x�b�h�̃T�C�Y
}Field;

void InitField(void);//�|���S���̏���������
void UninitField(void);//�|���S���̏I������
void UpdateField(void);//�|���S���̍X�V����
void DrawField(void);//�|���S���̕`�揈��

Field* GetField(void);
void SetFieldPos(D3DXVECTOR3 pos);
#endif _BED_H_