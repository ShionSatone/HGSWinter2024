//----------------------------------------
//
//���C�g����[light.cpp]
//Author fuma sato
//
//----------------------------------------

#include"main.h"
#include"light.h"
#include"input.h"
#include"game.h"

//�O���[�o���ϐ��錾
D3DLIGHT9 g_light[LIGHT_MAX];
D3DXVECTOR3 g_vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
float g_angle = 0.0f;
bool g_Input = false;
//----------------------
//����������
//----------------------
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCount = 0;

	g_Input = false;

	//���C�g���N���A����
	ZeroMemory(&g_light, sizeof(g_light));

	//------------------------------
	// �f�B���N�V���i�����C�g�̐ݒ�
	//------------------------------
	//���
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[0].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(0,&g_light[0]);
	//�L����
	pDevice->LightEnable(0, TRUE);

	//���
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[1].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(-0.9f, -0.8f, 0.8f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[1].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(1, &g_light[1]);
	//�L����
	pDevice->LightEnable(1, TRUE);

	//���
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[2].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[2].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(0.1f, -0.4f, -0.8f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[2].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(2, &g_light[2]);
	//�L����
	pDevice->LightEnable(2, TRUE);

	//���
	g_light[3].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[3].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[3].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(-0.3f, -0.4f, -0.3f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[3].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(3, &g_light[3]);
	//�L����
	pDevice->LightEnable(3, TRUE);

	////-----------------------
	//// �X�|�b�g���C�g�̐ݒ�
	////-----------------------
	////���
	//g_light[4].Type = D3DLIGHT_SPOT;
	////�g�U��
	//g_light[4].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	////����
	//g_light[4].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	////���ʔ��ˌ�
	//g_light[4].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	////�ʒu
	//g_light[4].Position = D3DXVECTOR3(0.0f, 2000.0f, 1.0f);
	////����
	//g_vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	////���K��
	//D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	//g_light[4].Direction = g_vecDir;
	////�͈�
	//g_light[4].Range = 3000.0f;
	////�R�[��������
	//g_light[4].Falloff = 0.01f;
	////����������
	//g_light[4].Attenuation0 = 0.1f;
	////�R�[���p�x(��)
	//g_light[4].Theta = D3DXToRadian(0.0f);
	////�R�[���p�x(�O)
	//g_light[4].Phi = D3DXToRadian(360.0f);
	////���C�g�Z�b�g
	//pDevice->SetLight(4, &g_light[4]);
	////�L����
	//pDevice->LightEnable(4, TRUE);

	////----------------------
	//// �|�C���g���C�g�̐ݒ�
	////----------------------
	////���
	//g_light[5].Type = D3DLIGHT_POINT;
	////�g�U��
	//g_light[5].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	////����
	//g_light[5].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	////���ʔ��ˌ�
	//g_light[5].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	////�ʒu
	//g_light[5].Position = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
	////�͈�
	//g_light[5].Range = 1000.0f;
	////����������(���)
	//g_light[5].Attenuation0 = 0.1f;
	////����������(����)
	//g_light[5].Attenuation1 = 0.0f;
	////����������(����*2)
	//g_light[5].Attenuation2 = 0.0f;
	////���C�g�Z�b�g
	//pDevice->SetLight(5, &g_light[5]);
	////�L����
	//pDevice->LightEnable(5, TRUE);
}

//-------------------
//�I������
//-------------------
void UninitLight(void)
{

}

//-------------------
//�X�V����
//-------------------
void UpdateLight(void)
{

}

//--------------------------
//�p�x�擾
//--------------------------
float GetLightAngle(void)
{
	return g_angle;
}