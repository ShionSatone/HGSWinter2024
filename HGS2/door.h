//=======================================
//
//�@�h�A [door.h]
//�@Author YOSHIDA YUTO
//
//=======================================

#ifndef _DOOR_H_
#define _DOOR_H_

//***************************************
// �C���N���[�h�t�@�C��
//***************************************
#include"main.h"

//***************************************
// �}�N����`
//***************************************
#define MAX_TEXTURE (64) // �e�N�X�`���̍ő吔

//***************************************
// �h�A�̍\����
//***************************************
typedef struct
{
	LPD3DXMESH pMesh;//���_���|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���|�C���^
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTURE];//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 rotDest;//�ړI�̌���
	D3DXVECTOR3 scale;//�傫��
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	DWORD dwNumMat;//�}�e���A����
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	int nIdxBedParent;
}Door;

//***************************************
// �v���g�^�C�v�錾
//***************************************
void InitDoor(void);//�h�A�̏���������
void UninitDoor(void);//�h�A�̂̏I������
void UpdateDoor(void);//�h�A�̂̍X�V����
void DrawDoor(void);//�h�A�̂̕`�揈��
Door* GetDoor(void);//�h�A�̎擾����
void SetDoorPos(D3DXVECTOR3 pos);//�h�A�̐ݒ菈��
#endif _DOOR_H_
