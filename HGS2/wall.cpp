//----------------------------------------
//
//�Ǐ���[wall.cpp]
//Author fuma sato
//
//----------------------------------------

#include"wall.h"
#include"camera.h"
#include"input.h"
#include "particle.h"

// �}�N����`
#define X_NAME "data\\MODEL\\madowindow.x"
#define NUM_FILE	(4)

//�O���[�o���ϐ��錾
Wall g_Wall[NUM_FILE];

const char* file[NUM_FILE] =
{
	"data\\MODEL\\madowindow.x",
	"data\\MODEL\\wall1.x"
};

//----------------------
//�|���S���̏���������
//----------------------
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Wall[0].pos = D3DXVECTOR3(0.0f, 0.0f, -130.0f);
	g_Wall[1].pos = D3DXVECTOR3(0.0f, 0.0f, 130.0f);
	g_Wall[2].pos = D3DXVECTOR3(250.0f, 0.0f, 0.0f);
	g_Wall[2].rot = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f);
	g_Wall[3].pos = D3DXVECTOR3(-250.0f, 0.0f, 0.0f);
	g_Wall[3].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);

	for (int i = 0; i < NUM_FILE; i++)
	{
		g_Wall[i].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		if (i == 0)
		{
			//X�t�@�C���ǂݍ���
			D3DXLoadMeshFromX
			(
				"data\\MODEL\\madowindow.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Wall[i].pBuffMat,
				NULL,
				&g_Wall[i].dwNumMat,
				&g_Wall[i].pMesh
			);
		}
		else if (i == 1)
		{
			//X�t�@�C���ǂݍ���
			D3DXLoadMeshFromX
			(
				"data\\MODEL\\wall1.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Wall[i].pBuffMat,
				NULL,
				&g_Wall[i].dwNumMat,
				&g_Wall[i].pMesh
			);
		}
		else if (i == 2)
		{
			//X�t�@�C���ǂݍ���
			D3DXLoadMeshFromX
			(
				"data\\MODEL\\bedwall.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Wall[i].pBuffMat,
				NULL,
				&g_Wall[i].dwNumMat,
				&g_Wall[i].pMesh
			);
		}
		else if (i == 3)
		{
			//X�t�@�C���ǂݍ���
			D3DXLoadMeshFromX
			(
				"data\\MODEL\\doowwall.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Wall[i].pBuffMat,
				NULL,
				&g_Wall[i].dwNumMat,
				&g_Wall[i].pMesh
			);
		}

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Wall[i].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Wall[i].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`��������
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Wall[i].apTexture[nCntMat]
				);
			}
		}
	}
}

//-------------------
//�|���S���I������
//-------------------
void UninitWall(void)
{
	for (int nCnt = 0; nCnt < NUM_FILE; nCnt++)
	{
		for (int i = 0; i < 64; i++)
		{
			if (g_Wall[nCnt].apTexture[i] != NULL)
			{
				g_Wall[nCnt].apTexture[i]->Release();
				g_Wall[nCnt].apTexture[i] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_Wall[nCnt].pMesh != NULL)
		{
			g_Wall[nCnt].pMesh->Release();
			g_Wall[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_Wall[nCnt].pBuffMat != NULL)
		{
			g_Wall[nCnt].pBuffMat->Release();
			g_Wall[nCnt].pBuffMat = NULL;
		}

		for (int i = 0; i < NUM_FILE; i++)
		{
			if (file[i] != NULL)
			{
				file[i] = NULL;
			}
		}
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateWall(void)
{
	
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int i = 0; i < NUM_FILE; i++)
	{
		//�}�g���b�N�X������
		D3DXMatrixIdentity(&g_Wall[i].mtxWorld);

		//�傫���̔��f
		D3DXMatrixScaling(&mtxScale, g_Wall[i].scale.x, g_Wall[i].scale.y, g_Wall[i].scale.z);
		D3DXMatrixMultiply(&g_Wall[i].mtxWorld, &g_Wall[i].mtxWorld, &mtxScale);

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[i].rot.y, g_Wall[i].rot.x, g_Wall[i].rot.z);
		D3DXMatrixMultiply(&g_Wall[i].mtxWorld, &g_Wall[i].mtxWorld, &mtxRot);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, g_Wall[i].pos.x, g_Wall[i].pos.y, g_Wall[i].pos.z);
		D3DXMatrixMultiply(&g_Wall[i].mtxWorld, &g_Wall[i].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Wall[i].mtxWorld);

		//���݂̃}�e���A���擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Wall[i].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Wall[i].dwNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			//�e�N�X�`��
			pDevice->SetTexture(0, g_Wall[i].apTexture[nCntMat]);

			//���f���`��
			g_Wall[i].pMesh->DrawSubset(nCntMat);
		}

		pDevice->SetMaterial(&matDef);
	}
}