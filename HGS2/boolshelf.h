//---------------------------------------
//
//�x�b�h����[present.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _BOOLSHELF_H_
#define _BOOLSHELF_H_

#include"main.h"

typedef struct
{
	LPD3DXMESH pMesh;//���_���|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���|�C���^
	LPDIRECT3DTEXTURE9 apTexture[64];
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posDef;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale,Size;
	D3DXMATRIX mtxWorld;
	DWORD dwNumMat;//�}�e���A����
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMinDef;
	D3DXVECTOR3 vtxMaxDef;
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxBoolShelfParent;
}BoolShelf;

void InitBoolShelf(void);//�|���S���̏���������
void UninitBoolShelf(void);//�|���S���̏I������
void UpdateBoolShelf(void);//�|���S���̍X�V����
void DrawBoolShelf(void);//�|���S���̕`�揈��

BoolShelf* GetBoolShelf(void);
void SetBoolShelfPos(D3DXVECTOR3 pos);

#endif _BOOLSHELF_H_
