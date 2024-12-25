//=================================
//
// ���̋O�� [meshorbit.h]
// Author:YOSHIDA YUUTO
//
//=================================

#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"main.h"

//****************************
//�}�N����`
//****************************
#define SOAD_WIDTH (10.0f) //����
#define SOAD_HEIGHT (10.0f) //����

//#define XVTX (50) //X�̒l
//#define ZVTX (50) //y�̒l

#define SOAD_VERTEX (20) //���_��
//#define INDEX (POLYGON + 2)  //�C���f�b�N�X
//#define POLYGON (((XVTX * ZVTX) * 2)) + (4 * (ZVTX - 1)) //�|���S����

//****************************
//���̋O���̍\����
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//���̋O���̈ʒu
	D3DXVECTOR3 rot;//���̋O���̌���
	D3DXCOLOR col;//�F
	D3DXMATRIX mtxWorldMeshSword;//���̋O���̃��[���h�}�g���b�N�X
	D3DXVECTOR3 Scal;
}MESHSOAD;

//****************************
//�v���g�^�C�v�錾
//****************************
void InitMeshSword(void);//���̋O���̏���������
void UninitMeshSword(void);//���̋O���̏I������
void UpdateMeshSword(void);//���̋O���̍X�V����
void DrawMeshSword(void);//���̋O���̕`�揈��
#endif