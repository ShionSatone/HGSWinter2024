//=======================================
//
//�@�� [desk.h]
//�@Author YOSHIDA YUTO
//
//=======================================

#ifndef _DESK_H_
#define _DESK_H_

//***************************************
// �C���N���[�h�t�@�C��
//***************************************
#include"main.h"

//***************************************
// �}�N����`
//***************************************
#define MAX_TEXTURE (64) // �e�N�X�`���̍ő吔

//***************************************
// ���̍\����
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
}Desk;

//***************************************
// �v���g�^�C�v�錾
//***************************************
void InitDesk(void);//���̏���������
void UninitDesk(void);//���̂̏I������
void UpdateDesk(void);//���̂̍X�V����
void DrawDesk(void);//���̂̕`�揈��
Desk* GetDesk(void);//���̎擾����
void SetDeskPos(D3DXVECTOR3 pos);//���̐ݒ菈��
#endif _DESK_H_
