//---------------------------------------
//
//�C������[socks.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _SOCKS_H_
#define _SOCKS_H_

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
	int nIdxSocksParent;
}Socks;

void InitSocks(void);//�|���S���̏���������
void UninitSocks(void);//�|���S���̏I������
void UpdateSocks(void);//�|���S���̍X�V����
void DrawSocks(void);//�|���S���̕`�揈��

Socks* GetSocks(void);
void SetSocksPos(D3DXVECTOR3 pos);
#endif _BED_H_