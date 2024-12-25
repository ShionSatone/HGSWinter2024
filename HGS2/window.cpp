//----------------------------------------
//
//������[window.cpp]
//Author fuma sato
//
//----------------------------------------

#include"window.h"
#include"camera.h"
#include"input.h"
#include "particle.h"

// �}�N����`
#define X_NAME "data\\MODEL\\window.x"

//�O���[�o���ϐ��錾
Window g_Window;
//----------------------
//�|���S���̏���������
//----------------------
void InitWindow(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Window.pos = D3DXVECTOR3(0.0f, 0.0f, -130.0f);
	g_Window.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Window.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Window.pBuffMat,
		NULL,
		&g_Window.dwNumMat,
		&g_Window.pMesh
	);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Window.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Window.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Window.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//�|���S���I������
//-------------------
void UninitWindow(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Window.apTexture[i]!=NULL)
		{
			g_Window.apTexture[i]->Release();
			g_Window.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_Window.pMesh != NULL)
	{
		g_Window.pMesh->Release();
		g_Window.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_Window.pBuffMat != NULL)
	{
		g_Window.pBuffMat->Release();
		g_Window.pBuffMat = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateWindow(void)
{
	if (GetKeyboradTrigger(DIK_K) == true)
	{
		SetParticle(D3DXVECTOR3(g_Window.pos.x, g_Window.pos.y + 50.0f, g_Window.pos.z), D3DXVECTOR3(1.0f, 1.0f, 1.0f), PARTICLE_TYPE_COLLECT);
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawWindow(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_Window.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_Window.scale.x, g_Window.scale.y, g_Window.scale.z);
	D3DXMatrixMultiply(&g_Window.mtxWorld, &g_Window.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Window.rot.y, g_Window.rot.x, g_Window.rot.z);
	D3DXMatrixMultiply(&g_Window.mtxWorld, &g_Window.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Window.pos.x, g_Window.pos.y, g_Window.pos.z);
	D3DXMatrixMultiply(&g_Window.mtxWorld, &g_Window.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Window.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Window.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Window.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_Window.apTexture[nCntMat]);

		//���f���`��
		g_Window.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// ���擾
//------------------------------
Window* GetWindow(void)
{
	return &g_Window;
}

//------------------------------
// ���ݒ�
//------------------------------
void SetWindowPos(D3DXVECTOR3 pos)
{
	g_Window.pos = pos;		// �ʒu�ݒ�
}