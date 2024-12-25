//---------------------------------------
//
//�Ǐ���[wall.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _WALL_H_
#define _WALL_H_

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
	int nIdxWallParent;
}Wall;

void InitWall(void);//�|���S���̏���������
void UninitWall(void);//�|���S���̏I������
void UpdateWall(void);//�|���S���̍X�V����
void DrawWall(void);//�|���S���̕`�揈��

Wall* GetWall(void);
void SetWallPos(D3DXVECTOR3 pos);

#endif _BED_H_