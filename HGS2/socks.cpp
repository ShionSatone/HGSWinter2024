//----------------------------------------
//
//�C������[socks.cpp]
//Author fuma sato
//
//----------------------------------------

#include"socks.h"
#include"camera.h"
#include"input.h"

// �}�N����`
#define X_NAME "data\\MODEL\\saku.x"

//�O���[�o���ϐ��錾
Socks g_Socks;
//----------------------
//�|���S���̏���������
//----------------------
void InitSocks(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Socks.pos = D3DXVECTOR3(300.0f, 0.0f, 100.0f);
	g_Socks.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Socks.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Socks.pBuffMat,
		NULL,
		&g_Socks.dwNumMat,
		&g_Socks.pMesh
	);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Socks.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Socks.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Socks.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//�|���S���I������
//-------------------
void UninitSocks(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Socks.apTexture[i]!=NULL)
		{
			g_Socks.apTexture[i]->Release();
			g_Socks.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_Socks.pMesh != NULL)
	{
		g_Socks.pMesh->Release();
		g_Socks.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_Socks.pBuffMat != NULL)
	{
		g_Socks.pBuffMat->Release();
		g_Socks.pBuffMat = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateSocks(void)
{

}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawSocks(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_Socks.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_Socks.scale.x, g_Socks.scale.y, g_Socks.scale.z);
	D3DXMatrixMultiply(&g_Socks.mtxWorld, &g_Socks.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Socks.rot.y, g_Socks.rot.x, g_Socks.rot.z);
	D3DXMatrixMultiply(&g_Socks.mtxWorld, &g_Socks.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Socks.pos.x, g_Socks.pos.y, g_Socks.pos.z);
	D3DXMatrixMultiply(&g_Socks.mtxWorld, &g_Socks.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Socks.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Socks.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Socks.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_Socks.apTexture[nCntMat]);

		//���f���`��
		g_Socks.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// ���擾
//------------------------------
Socks* GetSocks(void)
{
	return &g_Socks;
}

//------------------------------
// ���ݒ�
//------------------------------
void SetSocksPos(D3DXVECTOR3 pos)
{
	g_Socks.pos = pos;		// �ʒu�ݒ�
}