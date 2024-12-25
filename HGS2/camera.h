//---------------------------------------
//
//�J�����̒�`�E�錾[camera.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

#define CAMERA_WIDTH (90.0f)//����̍L��
#define CAMERA_MIN (10.0f)//����̍ŏ�
#define CAMERA_MAX (20000.0f)//����̍ő�

//�J�����\����
typedef struct
{
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	D3DXVECTOR3 posU;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
}Camera;

void InitCamera(void);//����������
void UninitCamera(void);//�I������
void UpdateCamera(void);//�X�V����
void SetCamera(void);//�`�揈��
Camera* GetCamera(void);

#endif _CAMERA_H_