//=======================================
//
//�@���� [chimney.cpp]
//�@Author YOSHIDA YUTO
//
//=======================================

//***************************************
// �C���N���[�h�t�@�C��
//***************************************
#include"chimney.h"
#include"camera.h"
#include"input.h"

//***************************************
// �}�N����`
//***************************************
#define X_NAME "data\\MODEL\\test.x"

//***************************************
// �O���[�o���ϐ��錾
//***************************************
Chimney g_Chimney;

//=======================================
// ���˂̏���������
//=======================================
void InitChimney(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Chimney.pos = D3DXVECTOR3(0.0f, 0.0f, 20.0f);
	g_Chimney.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Chimney.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Chimney.pBuffMat,
		NULL,
		&g_Chimney.dwNumMat,
		&g_Chimney.pMesh
	);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Chimney.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Chimney.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Chimney.apTexture[nCntMat]
			);
		}
	}
}
//=======================================
// ���˂̏I������
//=======================================
void UninitChimney(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (g_Chimney.apTexture[i] != NULL)
		{
			g_Chimney.apTexture[i]->Release();
			g_Chimney.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_Chimney.pMesh != NULL)
	{
		g_Chimney.pMesh->Release();
		g_Chimney.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_Chimney.pBuffMat != NULL)
	{
		g_Chimney.pBuffMat->Release();
		g_Chimney.pBuffMat = NULL;
	}
}

//=======================================
// ���˂̍X�V����
//=======================================
void UpdateChimney(void)
{

}

//=======================================
// ���˂̕`�揈��
//=======================================
void DrawChimney(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_Chimney.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_Chimney.scale.x, g_Chimney.scale.y, g_Chimney.scale.z);
	D3DXMatrixMultiply(&g_Chimney.mtxWorld, &g_Chimney.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Chimney.rot.y, g_Chimney.rot.x, g_Chimney.rot.z);
	D3DXMatrixMultiply(&g_Chimney.mtxWorld, &g_Chimney.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Chimney.pos.x, g_Chimney.pos.y, g_Chimney.pos.z);
	D3DXMatrixMultiply(&g_Chimney.mtxWorld, &g_Chimney.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Chimney.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Chimney.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Chimney.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_Chimney.apTexture[nCntMat]);

		//���f���`��
		g_Chimney.pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=======================================
// ���˂̎擾����
//=======================================
Chimney* GetChimney(void)
{
	return &g_Chimney;
}
//=======================================
// ���˂̐ݒ菈��
//=======================================
void SetChimneyPos(D3DXVECTOR3 pos)
{
	g_Chimney.pos = pos;
}
