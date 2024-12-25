//=======================================
//
//�@�� [chimney.cpp]
//�@Author YOSHIDA YUTO
//
//=======================================

//***************************************
// �C���N���[�h�t�@�C��
//***************************************
#include"desk.h"
#include"camera.h"
#include"input.h"
#include "player.h"

//***************************************
// �}�N����`
//***************************************
#define X_NAME "data\\MODEL\\desk.x"

//***************************************
// �O���[�o���ϐ��錾
//***************************************
Desk g_Desk;

//=======================================
// ���̏���������
//=======================================
void InitDesk(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Desk.pos = D3DXVECTOR3(-70.0f, 0.0f, 10.0f);
	g_Desk.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Desk.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Desk.pBuffMat,
		NULL,
		&g_Desk.dwNumMat,
		&g_Desk.pMesh
	);

	//���_��
	g_Desk.nNumVtx = g_Desk.pMesh->GetNumVertices();
	//���_�T�C�Y
	g_Desk.sizeFVF = D3DXGetFVFVertexSize(g_Desk.pMesh->GetFVF());
	//���_�o�b�t�@�̎擾
	g_Desk.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Desk.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_Desk.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Desk.pVtxBuff;

		if (vtx.x > g_Desk.vtxMax.x)
		{
			g_Desk.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_Desk.vtxMin.x)
		{
			g_Desk.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_Desk.vtxMax.y)
		{
			g_Desk.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_Desk.vtxMin.y)
		{
			g_Desk.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_Desk.vtxMax.z)
		{
			g_Desk.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_Desk.vtxMin.z)
		{
			g_Desk.vtxMin.z = vtx.z;
		}

		g_Desk.pVtxBuff += g_Desk.sizeFVF;
	}
	g_Desk.Size.x = g_Desk.vtxMax.x - g_Desk.vtxMin.x;
	g_Desk.Size.y = g_Desk.vtxMax.y - g_Desk.vtxMin.y;
	g_Desk.Size.z = g_Desk.vtxMax.z - g_Desk.vtxMin.z;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Desk.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Desk.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Desk.apTexture[nCntMat]
			);
		}
	}
}
//=======================================
// ���̏I������
//=======================================
void UninitDesk(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (g_Desk.apTexture[i] != NULL)
		{
			g_Desk.apTexture[i]->Release();
			g_Desk.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_Desk.pMesh != NULL)
	{
		g_Desk.pMesh->Release();
		g_Desk.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_Desk.pBuffMat != NULL)
	{
		g_Desk.pBuffMat->Release();
		g_Desk.pBuffMat = NULL;
	}
}

//=======================================
// ���̍X�V����
//=======================================
void UpdateDesk(void)
{
	CollisionObj(g_Desk.pos, g_Desk.Size);//�v���C���[�Ƃ̓����蔻��
}

//=======================================
// ���̕`�揈��
//=======================================
void DrawDesk(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_Desk.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_Desk.scale.x, g_Desk.scale.y, g_Desk.scale.z);
	D3DXMatrixMultiply(&g_Desk.mtxWorld, &g_Desk.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Desk.rot.y, g_Desk.rot.x, g_Desk.rot.z);
	D3DXMatrixMultiply(&g_Desk.mtxWorld, &g_Desk.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Desk.pos.x, g_Desk.pos.y, g_Desk.pos.z);
	D3DXMatrixMultiply(&g_Desk.mtxWorld, &g_Desk.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Desk.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Desk.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Desk.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_Desk.apTexture[nCntMat]);

		//���f���`��
		g_Desk.pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=======================================
// ���̎擾����
//=======================================
Desk* GetDesk(void)
{
	return &g_Desk;
}
//=======================================
// ���̐ݒ菈��
//=======================================
void SetDeskPos(D3DXVECTOR3 pos)
{
	g_Desk.pos = pos;
}
