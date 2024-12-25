//=================================
//
// ���̋O�� [meshorbit.h]
// Author:YOSHIDA YUUTO
//
//=================================

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"meshorbit.h"
#include "input.h"
#include "player.h"

//****************************
//�}�N����`
//****************************
#define MAX_ORBIT (64) //���_��

//****************************
//�O���[�o���ϐ��錾
//****************************
LPDIRECT3DTEXTURE9 g_pTextureMeshSword = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSword = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshSword = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MESHSOAD g_MeshSword;

//===============================
//���b�V���t�B�[���h�̏���������
//===============================
void InitMeshSword(void)
{
	int nCnt = 0;

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();//�f�o�C�X���擾

		//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\orbit.png",
		&g_pTextureMeshSword);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_ORBIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSword,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_ORBIT,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshSword,
		NULL);

	g_MeshSword.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshSword.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshSword.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_MeshSword.Scal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshSword->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_���W�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_���W�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshSword->Unlock();

	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	g_pIdxBuffMeshSword->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MAX_ORBIT; nCnt++)
	{
		pIdx[nCnt] = nCnt;
	}
	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshSword->Unlock();

}

//===============================
//���b�V���t�B�[���h�̏I������
//===============================ccc
void UninitMeshSword(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureMeshSword != NULL)
	{
		g_pTextureMeshSword->Release();
		g_pTextureMeshSword = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshSword != NULL)
	{
		g_pVtxBuffMeshSword->Release();
		g_pVtxBuffMeshSword = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshSword != NULL)
	{
		g_pIdxBuffMeshSword->Release();
		g_pIdxBuffMeshSword = NULL;
	}
}

//===============================
//���b�V���t�B�[���h�̍X�V����
//===============================
void UpdateMeshSword(void)
{

	Player* pPlayer = GetPlayer();  // �v���C���[�����擾
	VERTEX_3D* pVtx;

	int vtxCnt = 0;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshSword->Lock(0, 0, (void**)&pVtx, 0);

	if (pPlayer->motionType == MOTIONTYPE_ACTION)
	{
		for (int nCnt = 2; nCnt < MAX_ORBIT; nCnt += 2, vtxCnt += 2)
		{
			pVtx[nCnt].pos.x = pVtx[vtxCnt].pos.x;
			pVtx[nCnt].pos.y = pVtx[vtxCnt].pos.y;
			pVtx[nCnt].pos.z = pVtx[vtxCnt].pos.z;

			pVtx[nCnt + 1].pos.x = pVtx[vtxCnt + 1].pos.x;
			pVtx[nCnt + 1].pos.y = pVtx[vtxCnt + 1].pos.y;
			pVtx[nCnt + 1].pos.z = pVtx[vtxCnt + 1].pos.z;
		}
		pVtx[0].pos.x = pPlayer->SwordMtxWorld._41;
		pVtx[0].pos.y = pPlayer->SwordMtxWorld._42;
		pVtx[0].pos.z = pPlayer->SwordMtxWorld._43;

		pVtx[1].pos.x = pPlayer->aModel[MODEL_SWORD].mtxWorld._41;
		pVtx[1].pos.y = pPlayer->aModel[MODEL_SWORD].mtxWorld._42;
		pVtx[1].pos.z = pPlayer->aModel[MODEL_SWORD].mtxWorld._43;

	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshSword->Unlock();
}

//===============================
//���b�V���t�B�[���h�̕`�揈��
//===============================
void DrawMeshSword(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	Player* pPlayer = GetPlayer();  // �v���C���[�����擾

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	if (pPlayer->motionType == MOTIONTYPE_ACTION)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_MeshSword.mtxWorldMeshSword);

		pDevice->SetRenderState(D3DRS_CULLMODE, TRUE);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshSword.rot.y, g_MeshSword.rot.x, g_MeshSword.rot.z);
		D3DXMatrixMultiply(&g_MeshSword.mtxWorldMeshSword, &g_MeshSword.mtxWorldMeshSword, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_MeshSword.pos.x, g_MeshSword.pos.y, g_MeshSword.pos.z);
		D3DXMatrixMultiply(&g_MeshSword.mtxWorldMeshSword, &g_MeshSword.mtxWorldMeshSword, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshSword.mtxWorldMeshSword);

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshSword, 0, sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshSword);

		//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshSword);

		//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_ORBIT, 0, 1);
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
