//----------------------------------------
//
//�v���[���g����[model.cpp]
//Author fuma sato
//
//----------------------------------------

#include"bed.h"
#include"camera.h"
#include"input.h"
#include "particle.h"
#include "player.h"

// �}�N����`
#define X_NAME "data\\MODEL\\bed.x"

//�O���[�o���ϐ��錾
Bed g_Bed;
//----------------------
//�|���S���̏���������
//----------------------
void InitBed(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Bed.pos = D3DXVECTOR3(190.0f, 0.0f, -40.0f);
	g_Bed.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Bed.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Bed.pBuffMat,
		NULL,
		&g_Bed.dwNumMat,
		&g_Bed.pMesh
	);

	//���_��
	g_Bed.nNumVtx = g_Bed.pMesh->GetNumVertices();
	//���_�T�C�Y
	g_Bed.sizeFVF = D3DXGetFVFVertexSize(g_Bed.pMesh->GetFVF());
	//���_�o�b�t�@�̎擾
	g_Bed.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Bed.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_Bed.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Bed.pVtxBuff;

		if (vtx.x > g_Bed.vtxMax.x)
		{
			g_Bed.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_Bed.vtxMin.x)
		{
			g_Bed.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_Bed.vtxMax.y)
		{
			g_Bed.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_Bed.vtxMin.y)
		{
			g_Bed.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_Bed.vtxMax.z)
		{
			g_Bed.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_Bed.vtxMin.z)
		{
			g_Bed.vtxMin.z = vtx.z;
		}

		g_Bed.pVtxBuff += g_Bed.sizeFVF;
	}
	g_Bed.Size.x = g_Bed.vtxMax.x - g_Bed.vtxMin.x;
	g_Bed.Size.y = g_Bed.vtxMax.y - g_Bed.vtxMin.y;
	g_Bed.Size.z = g_Bed.vtxMax.z - g_Bed.vtxMin.z;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Bed.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Bed.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_Bed.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//�|���S���I������
//-------------------
void UninitBed(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_Bed.apTexture[i]!=NULL)
		{
			g_Bed.apTexture[i]->Release();
			g_Bed.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_Bed.pMesh != NULL)
	{
		g_Bed.pMesh->Release();
		g_Bed.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_Bed.pBuffMat != NULL)
	{
		g_Bed.pBuffMat->Release();
		g_Bed.pBuffMat = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateBed(void)
{
	if (GetKeyboradTrigger(DIK_K) == true)
	{
		SetParticle(D3DXVECTOR3(g_Bed.pos.x, g_Bed.pos.y + 50.0f, g_Bed.pos.z), D3DXVECTOR3(1.0f, 1.0f, 1.0f), PARTICLE_TYPE_COLLECT);
	}

	CollisionObj(g_Bed.pos,g_Bed.Size);//�����蔻��
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawBed(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_Bed.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_Bed.scale.x, g_Bed.scale.y, g_Bed.scale.z);
	D3DXMatrixMultiply(&g_Bed.mtxWorld, &g_Bed.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Bed.rot.y, g_Bed.rot.x, g_Bed.rot.z);
	D3DXMatrixMultiply(&g_Bed.mtxWorld, &g_Bed.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Bed.pos.x, g_Bed.pos.y, g_Bed.pos.z);
	D3DXMatrixMultiply(&g_Bed.mtxWorld, &g_Bed.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Bed.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Bed.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Bed.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_Bed.apTexture[nCntMat]);

		//���f���`��
		g_Bed.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// ���擾
//------------------------------
Bed* GetBed(void)
{
	return &g_Bed;
}

//------------------------------
// ���ݒ�
//------------------------------
void SetBedPos(D3DXVECTOR3 pos)
{
	g_Bed.pos = pos;		// �ʒu�ݒ�
}

void CollisionBed(void)
{
}
