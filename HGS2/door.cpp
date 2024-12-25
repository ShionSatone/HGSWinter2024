//=======================================
//
//�@�h�A [door.cpp]
//�@Author YOSHIDA YUTO
//
//=======================================

//***************************************
// �C���N���[�h�t�@�C��
//***************************************
#include"door.h"
#include"camera.h"
#include"input.h"
#include "santa.h"
#include "blacksanta.h"

//***************************************
// �}�N����`
//***************************************
#define X_NAME "data\\MODEL\\door.x"

//***************************************
// �O���[�o���ϐ��錾
//***************************************
Door g_Door;

//=======================================
// �h�A�̏���������
//=======================================
void InitDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Door.pos = D3DXVECTOR3(-250.0f, 0.0f, 0.0f);
	g_Door.rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	g_Door.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Door.pBuffMat,
		NULL,
		&g_Door.dwNumMat,
		&g_Door.pMesh
	);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Door.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Door.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Door.apTexture[nCntMat]
			);
		}
	}
}
//=======================================
// �h�A�̏I������
//=======================================
void UninitDoor(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (g_Door.apTexture[i] != NULL)
		{
			g_Door.apTexture[i]->Release();
			g_Door.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_Door.pMesh != NULL)
	{
		g_Door.pMesh->Release();
		g_Door.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_Door.pBuffMat != NULL)
	{
		g_Door.pBuffMat->Release();
		g_Door.pBuffMat = NULL;
	}
}

//=======================================
// �h�A�̍X�V����
//=======================================
void UpdateDoor(void)
{
	Santa* pSanta = GetSanta();//�T���^���擾
	BlackSanta* pBlacSanta = GetBlackSanta();

	if (pSanta->Startpos.z == g_Door.pos.z && pSanta->bUse == true || pBlacSanta->pos.z == g_Door.pos.z && pBlacSanta->bUse == true)
	{//�T���^���g���Ă���
		g_Door.rotDest.y = 0.0f; //�h�A���󂢂�
	}
	else
	{
		g_Door.rotDest.y = D3DX_PI * 0.5f;//�h�A�����܂���
	}

	g_Door.rot.y += (g_Door.rotDest.y - g_Door.rot.y) * 0.05f;//�h�A�̌�����ړI�̌����ɂ���
}

//=======================================
// �h�A�̕`�揈��
//=======================================
void DrawDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_Door.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_Door.scale.x, g_Door.scale.y, g_Door.scale.z);
	D3DXMatrixMultiply(&g_Door.mtxWorld, &g_Door.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Door.rot.y, g_Door.rot.x, g_Door.rot.z);
	D3DXMatrixMultiply(&g_Door.mtxWorld, &g_Door.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Door.pos.x, g_Door.pos.y, g_Door.pos.z);
	D3DXMatrixMultiply(&g_Door.mtxWorld, &g_Door.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Door.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Door.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Door.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_Door.apTexture[nCntMat]);

		//���f���`��
		g_Door.pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=======================================
// �h�A�̎擾����
//=======================================
Door* GetDoor(void)
{
	return &g_Door;
}
//=======================================
// �h�A�̐ݒ菈��
//=======================================
void SetDoorPos(D3DXVECTOR3 pos)
{
	g_Door.pos = pos;
}
