//=======================================
//
//�@�֎q [chair.cpp]
//�@Author YOSHIDA YUTO
//
//=======================================

//***************************************
// �C���N���[�h�t�@�C��
//***************************************
#include"chair.h"
#include"camera.h"
#include"input.h"

//***************************************
// �}�N����`
//***************************************
#define X_NAME "data\\MODEL\\chair.x"

//***************************************
// �O���[�o���ϐ��錾
//***************************************
Chair g_Chair;

//=======================================
// �֎q�̏���������
//=======================================
void InitChair(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Chair.pos = D3DXVECTOR3(-40.0f, 0.0f, 0.0f);
	g_Chair.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Chair.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Chair.pBuffMat,
		NULL,
		&g_Chair.dwNumMat,
		&g_Chair.pMesh
	);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Chair.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Chair.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Chair.apTexture[nCntMat]
			);
		}
	}
}
//=======================================
// �֎q�̏I������
//=======================================
void UninitChair(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (g_Chair.apTexture[i] != NULL)
		{
			g_Chair.apTexture[i]->Release();
			g_Chair.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_Chair.pMesh != NULL)
	{
		g_Chair.pMesh->Release();
		g_Chair.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_Chair.pBuffMat != NULL)
	{
		g_Chair.pBuffMat->Release();
		g_Chair.pBuffMat = NULL;
	}
}

//=======================================
// �֎q�̍X�V����
//=======================================
void UpdateChair(void)
{

}

//=======================================
// �֎q�̕`�揈��
//=======================================
void DrawChair(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_Chair.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_Chair.scale.x, g_Chair.scale.y, g_Chair.scale.z);
	D3DXMatrixMultiply(&g_Chair.mtxWorld, &g_Chair.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Chair.rot.y, g_Chair.rot.x, g_Chair.rot.z);
	D3DXMatrixMultiply(&g_Chair.mtxWorld, &g_Chair.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Chair.pos.x, g_Chair.pos.y, g_Chair.pos.z);
	D3DXMatrixMultiply(&g_Chair.mtxWorld, &g_Chair.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Chair.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Chair.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Chair.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_Chair.apTexture[nCntMat]);

		//���f���`��
		g_Chair.pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=======================================
// �֎q�̎擾����
//=======================================
Chair* GetChair(void)
{
	return &g_Chair;
}
//=======================================
// �֎q�̐ݒ菈��
//=======================================
void SetChairPos(D3DXVECTOR3 pos)
{
	g_Chair.pos = pos;
}
