//=======================================
//
//�@�֎q [chair.h]
//�@Author YOSHIDA YUTO
//
//=======================================

#ifndef _CHAIR_H_
#define _CHAIR_H_

//***************************************
// �C���N���[�h�t�@�C��
//***************************************
#include"main.h"

//***************************************
// �}�N����`
//***************************************
#define MAX_TEXTURE (64) // �e�N�X�`���̍ő吔

//***************************************
// �֎q�̍\����
//***************************************
typedef struct
{
	LPD3DXMESH pMesh;//���_���|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���|�C���^
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTURE];//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 scale;//�傫��
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	DWORD dwNumMat;//�}�e���A����
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxBedParent;
}Chair;

//***************************************
// �v���g�^�C�v�錾
//***************************************
void InitChair(void);//�֎q�̏���������
void UninitChair(void);//�֎q�̂̏I������
void UpdateChair(void);//�֎q�̂̍X�V����
void DrawChair(void);//�֎q�̂̕`�揈��
Chair* GetChair(void);//�֎q�̎擾����
void SetChairPos(D3DXVECTOR3 pos);//�֎q�̐ݒ菈��
#endif _CHAIR_H_
