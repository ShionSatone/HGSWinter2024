//----------------------------------------
//
//�v���[���g����[model.cpp]
//Author fuma sato
//
//----------------------------------------
#include"boolshelf.h"
#include"camera.h"
#include"input.h"
#include "particle.h"
#include "player.h"

// �}�N����`
#define X_NAME "data\\MODEL\\boolshelf.x"

//�O���[�o���ϐ��錾
BoolShelf g_BoolShelf;
//----------------------
//�|���S���̏���������
//----------------------
void InitBoolShelf(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_BoolShelf.pos = D3DXVECTOR3(80.0f, 0.0f,-20.0f);
	g_BoolShelf.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BoolShelf.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		X_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BoolShelf.pBuffMat,
		NULL,
		&g_BoolShelf.dwNumMat,
		&g_BoolShelf.pMesh
	);

	//���_��
	g_BoolShelf.nNumVtx = g_BoolShelf.pMesh->GetNumVertices();
	//���_�T�C�Y
	g_BoolShelf.sizeFVF = D3DXGetFVFVertexSize(g_BoolShelf.pMesh->GetFVF());
	//���_�o�b�t�@�̎擾
	g_BoolShelf.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_BoolShelf.pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < g_BoolShelf.nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_BoolShelf.pVtxBuff;

		if (vtx.x > g_BoolShelf.vtxMax.x)
		{
			g_BoolShelf.vtxMax.x = vtx.x;
		}
		if (vtx.x < g_BoolShelf.vtxMin.x)
		{
			g_BoolShelf.vtxMin.x = vtx.x;
		}
		if (vtx.y > g_BoolShelf.vtxMax.y)
		{
			g_BoolShelf.vtxMax.y = vtx.y;
		}
		if (vtx.y < g_BoolShelf.vtxMin.y)
		{
			g_BoolShelf.vtxMin.y = vtx.y;
		}
		if (vtx.z > g_BoolShelf.vtxMax.z)
		{
			g_BoolShelf.vtxMax.z = vtx.z;
		}
		if (vtx.z < g_BoolShelf.vtxMin.z)
		{
			g_BoolShelf.vtxMin.z = vtx.z;
		}

		g_BoolShelf.pVtxBuff += g_BoolShelf.sizeFVF;
	}
	g_BoolShelf.Size.x = g_BoolShelf.vtxMax.x - g_BoolShelf.vtxMin.x;
	g_BoolShelf.Size.y = g_BoolShelf.vtxMax.y - g_BoolShelf.vtxMin.y;
	g_BoolShelf.Size.z = g_BoolShelf.vtxMax.z - g_BoolShelf.vtxMin.z;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_BoolShelf.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_BoolShelf.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`��������
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_BoolShelf.apTexture[nCntMat]
			);
		}
	}
}

//-------------------
//�|���S���I������
//-------------------
void UninitBoolShelf(void)
{
	for (int i = 0; i < 64; i++)
	{
		if (g_BoolShelf.apTexture[i]!=NULL)
		{
			g_BoolShelf.apTexture[i]->Release();
			g_BoolShelf.apTexture[i] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_BoolShelf.pMesh != NULL)
	{
		g_BoolShelf.pMesh->Release();
		g_BoolShelf.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_BoolShelf.pBuffMat != NULL)
	{
		g_BoolShelf.pBuffMat->Release();
		g_BoolShelf.pBuffMat = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateBoolShelf(void)
{
	if (GetKeyboradTrigger(DIK_K) == true)
	{
		SetParticle(D3DXVECTOR3(g_BoolShelf.pos.x, g_BoolShelf.pos.y + 50.0f, g_BoolShelf.pos.z), D3DXVECTOR3(1.0f, 1.0f, 1.0f), PARTICLE_TYPE_COLLECT);
	}

	CollisionObj(g_BoolShelf.pos,g_BoolShelf.Size);
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawBoolShelf(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&g_BoolShelf.mtxWorld);

	//�傫���̔��f
	D3DXMatrixScaling(&mtxScale, g_BoolShelf.scale.x, g_BoolShelf.scale.y, g_BoolShelf.scale.z);
	D3DXMatrixMultiply(&g_BoolShelf.mtxWorld, &g_BoolShelf.mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_BoolShelf.rot.y, g_BoolShelf.rot.x, g_BoolShelf.rot.z);
	D3DXMatrixMultiply(&g_BoolShelf.mtxWorld, &g_BoolShelf.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_BoolShelf.pos.x, g_BoolShelf.pos.y, g_BoolShelf.pos.z);
	D3DXMatrixMultiply(&g_BoolShelf.mtxWorld, &g_BoolShelf.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_BoolShelf.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_BoolShelf.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_BoolShelf.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`��
		pDevice->SetTexture(0, g_BoolShelf.apTexture[nCntMat]);

		//���f���`��
		g_BoolShelf.pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}

//------------------------------
// ���擾
//------------------------------
BoolShelf* GetBoolShelf(void)
{
	return &g_BoolShelf;
}

//------------------------------
// ���ݒ�
//------------------------------
void SetBoolShelfPos(D3DXVECTOR3 pos)
{
	g_BoolShelf.pos = pos;		// �ʒu�ݒ�
}
