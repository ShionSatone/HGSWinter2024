//----------------------------------------
//
//�J��������[camera.cpp]
//Author fuma sato
//
//----------------------------------------

#include"camera.h"

//�O���[�o���ϐ��錾
Camera g_camera;//�J�������
//----------------------
//����������
//----------------------
void InitCamera(void)
{
	//�J�����ݒ�
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -150.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_camera.rot = D3DXVECTOR3(-atan2f(120.0f, 300.0f), 0.0f, 0.0f);
}

//-------------------
//�I������
//-------------------
void UninitCamera(void)
{

}

//-------------------
//�X�V����
//-------------------
void UpdateCamera(void)
{

}

//-------------------
//�`�揈��
//-------------------
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�r���[�}�g���b�N�X������
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH
	(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.posU
	);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH
	(
		&g_camera.mtxProjection,
		D3DXToRadian(CAMERA_WIDTH),//���E�̍L��
		(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,//�䗦
		CAMERA_MIN,//�ǂ�����
		CAMERA_MAX//�ǂ��܂�
	);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//--------------------------
//�J�����擾
//--------------------------
Camera* GetCamera(void)
{
	return &g_camera;
}