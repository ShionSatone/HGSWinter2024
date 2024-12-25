//----------------------------------------
//
//�v���[���g����[model.cpp]
//Author fuma sato
//
//----------------------------------------

#include"present.h"
#include"camera.h"
#include"input.h"

#if 0
// �}�N����`
#define X_NAME "data\\MODEL\\prezent.x"

//�O���[�o���ϐ��錾
Present g_Present;
//----------------------
//�|���S���̏���������
//----------------------
void InitPresent(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Present.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Present.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Present.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Present.pBuffMat,
		NULL,
		&g_Present.dwNumMat,
		&g_Present.pMesh
	);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Present.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Present.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Present.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//�|���S���I������
//-------------------
void UninitPresent(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Present.apTexture[i]!=NULL)
		{
			g_Present.apTexture[i]->Release();
			g_Present.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_Present.pMesh != NULL)
	{
		g_Present.pMesh->Release();
		g_Present.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_Present.pBuffMat != NULL)
	{
		g_Present.pBuffMat->Release();
		g_Present.pBuffMat = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdatePresent(void)
{

}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawPresent(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_Present.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_Present.scale.x, g_Present.scale.y, g_Present.scale.z);
	D3DXMatrixMultiply(&g_Present.mtxWorld, &g_Present.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Present.rot.y, g_Present.rot.x, g_Present.rot.z);
	D3DXMatrixMultiply(&g_Present.mtxWorld, &g_Present.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Present.pos.x, g_Present.pos.y, g_Present.pos.z);
	D3DXMatrixMultiply(&g_Present.mtxWorld, &g_Present.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Present.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Present.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Present.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_Present.apTexture[nCntMat]);

		//���f���`��
		g_Present.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// ���擾
//------------------------------
Present* GetPresent(void)
{
	return &g_Present;
}

//------------------------------
// ���ݒ�
//------------------------------
void SetPresentPos(D3DXVECTOR3 pos)
{
	g_Present.pos = pos;		// �ʒu�ݒ�
}
#endif