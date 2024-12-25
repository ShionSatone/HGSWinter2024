//----------------------------------------
//
//�v���[���g����[model.cpp]
//Author fuma sato
//
//----------------------------------------

#include"field.h"
#include"camera.h"
#include"input.h"
#include "particle.h"
#include "player.h"

// �}�N����`
#define X_NAME "data\\MODEL\\yuka.x"

//�O���[�o���ϐ��錾
Field g_Field;
//----------------------
//�|���S���̏���������
//----------------------
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Field.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_Field.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Field.pBuffMat,
		NULL,
		&g_Field.dwNumMat,
		&g_Field.pMesh
	);

	//���_��
	g_Field.nNumVtx = g_Field.pMesh->GetNumVertices();
	//���_�T�C�Y
	g_Field.sizeFVF = D3DXGetFVFVertexSize(g_Field.pMesh->GetFVF());
	//���_�o�b�t�@�̎擾
	g_Field.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Field.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_Field.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Field.pVtxBuff;

		if (vtx.x > g_Field.vtxMax.x)
		{
			g_Field.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_Field.vtxMin.x)
		{
			g_Field.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_Field.vtxMax.y)
		{
			g_Field.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_Field.vtxMin.y)
		{
			g_Field.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_Field.vtxMax.z)
		{
			g_Field.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_Field.vtxMin.z)
		{
			g_Field.vtxMin.z = vtx.z;
		}

		g_Field.pVtxBuff += g_Field.sizeFVF;
	}
	g_Field.Size.x = g_Field.vtxMax.x - g_Field.vtxMin.x;
	g_Field.Size.y = g_Field.vtxMax.y - g_Field.vtxMin.y;
	g_Field.Size.z = g_Field.vtxMax.z - g_Field.vtxMin.z;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Field.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Field.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Field.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//�|���S���I������
//-------------------
void UninitField(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Field.apTexture[i]!=NULL)
		{
			g_Field.apTexture[i]->Release();
			g_Field.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_Field.pMesh != NULL)
	{
		g_Field.pMesh->Release();
		g_Field.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_Field.pBuffMat != NULL)
	{
		g_Field.pBuffMat->Release();
		g_Field.pBuffMat = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateField(void)
{
	//CollisionObj(g_Field.pos,g_Field.Size);//�����蔻��
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_Field.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_Field.scale.x, g_Field.scale.y, g_Field.scale.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field.rot.y, g_Field.rot.x, g_Field.rot.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Field.pos.x, g_Field.pos.y, g_Field.pos.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Field.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Field.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Field.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_Field.apTexture[nCntMat]);

		//���f���`��
		g_Field.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// ���擾
//------------------------------
Field* GetField(void)
{
	return &g_Field;
}

//------------------------------
// ���ݒ�
//------------------------------
void SetFieldPos(D3DXVECTOR3 pos)
{
	g_Field.pos = pos;		// �ʒu�ݒ�
}

void CollisionField(void)
{
}
