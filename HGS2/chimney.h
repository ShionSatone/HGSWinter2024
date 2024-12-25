//=======================================
//
//�@���� [chimney.h]
//�@Author YOSHIDA YUTO
//
//=======================================

#ifndef _CHIMNEY_H_
#define _CHIMNEY_H_

//***************************************
// �C���N���[�h�t�@�C��
//***************************************
#include"main.h"

//***************************************
// �}�N����`
//***************************************
#define MAX_TEXTURE (64) // �e�N�X�`���̍ő吔

//***************************************
// ���˂̍\����
//***************************************
typedef struct
{
	LPD3DXMESH pMesh;//���_���|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���|�C���^
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTURE];//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 scale;//�傫��
	D3DXVECTOR3 vtxMax,vtxMin,Size;//�傫��
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	DWORD dwNumMat;//�}�e���A����
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxBedParent;
}Chimney;

//***************************************
// �v���g�^�C�v�錾
//***************************************
void InitChimney(void);//���˂̏���������
void UninitChimney(void);//���˂̂̏I������
void UpdateChimney(void);//���˂̂̍X�V����
void DrawChimney(void);//���˂̂̕`�揈��
Chimney* GetChimney(void);//���˂̎擾����
void SetChimneyPos(D3DXVECTOR3 pos);//���˂̐ݒ菈��
#endif _CHIMNEY_H_
