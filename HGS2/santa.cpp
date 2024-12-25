//----------------------------------------
//
//���f���\������[santa.cpp]
//Author fuma sato
//
//----------------------------------------

#include"santa.h"
#include"game.h"
#include"shadow.h"
#include"input.h"
#include"file.h"
#include"particle.h"
#include"life.h"
#include"bed.h"
#include"present.h"

//�O���[�o���ϐ��錾
Santa g_Santa;

static MOTION_INFO g_SantaMotion[] =
{
	true,
	2,
	{
	   {
		  80,
		  {
			 {
				 0.0f,-2.3f,0.0f,-0.03f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,-0.03f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.88f
			 },
			  {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.19f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-0.75f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-0.41f
			 },
			 {
			   0.0f,0.0f,0.0f,0.16f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.09f,0.0f,0.0f
			 },
			 {
				  0.0f,0.0f,0.0f,0.16f,0.0f,0.0f
			 },
			 {
				  0.0f,0.0f,0.0f,-0.09f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 },
		  }
	   },
	   {
		  80,
		  {
			 {
			   0.0f,-3.2f,0.0f,-0.19f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.22f,0.0f,1.13f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.31f
			 },
			 {
			   0.0f,0.0f,0.0f,0.22f,0.0f,-1.13f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-0.31f
			 },
			 {
			   0.0f,0.0f,0.0f,0.53f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.31f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.53f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.31f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.03f,0.0f,0.0f
			 },
		  }
	   }
	}
};

//----------------------
//�|���S���̏���������
//----------------------
void InitSanta(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Santa.pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_Santa.posOld = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_Santa.Startpos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_Santa.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Santa.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Santa.Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Santa.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Santa.nLife = SANTA_LIFE;
	g_Santa.state = SANTASTATE_NORMAL;
	g_Santa.nIdxShadow = -1;
	g_Santa.nIdxLife = -1;
	g_Santa.pStage = NULL;

	g_Santa.bLoopMotion = false;
	g_Santa.motionType = MOTIONTYPE_NEUTRAL;
	g_Santa.nCounterMotion = 0;
	g_Santa.nKey = -1;
	g_Santa.nNumKey = 0;
	g_Santa.nNumMotion = NUM_MOTION_SANTA;
	g_Santa.bPresent = false;
	g_Santa.bUse = false;

	LoadModel();

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		SANTA_BODY_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Santa.aModel[0].pBuffMat,
		NULL,
		&g_Santa.aModel[0].dwNumMat,
		&g_Santa.aModel[0].pMesh
	);

	g_Santa.nNumModel = NUM_MODEL_SANTA;

	int nCntModel;
	for (nCntModel = 0; nCntModel < g_Santa.nNumModel; nCntModel++)
	{

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Santa.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Santa.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`��������
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Santa.aModel[nCntModel].apTexture[nCntMat]
				);
			}
		}

		//���_��
		g_Santa.aModel[nCntModel].nNumVtx = g_Santa.aModel[nCntModel].pMesh->GetNumVertices();
		//���_�T�C�Y
		g_Santa.aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_Santa.aModel[nCntModel].pMesh->GetFVF());
		//���_�o�b�t�@�̎擾
		g_Santa.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Santa.aModel[nCntModel].pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < g_Santa.aModel[nCntModel].nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Santa.aModel[nCntModel].pVtxBuff;

			if (vtx.x > g_Santa.aModel[nCntModel].vtxMax.x)
			{
				g_Santa.aModel[nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.x < g_Santa.aModel[nCntModel].vtxMin.x)
			{
				g_Santa.aModel[nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y > g_Santa.aModel[nCntModel].vtxMax.y)
			{
				g_Santa.aModel[nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.y < g_Santa.aModel[nCntModel].vtxMin.y)
			{
				g_Santa.aModel[nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z > g_Santa.aModel[nCntModel].vtxMax.z)
			{
				g_Santa.aModel[nCntModel].vtxMax.z = vtx.z;
			}
			if (vtx.z < g_Santa.aModel[nCntModel].vtxMin.z)
			{
				g_Santa.aModel[nCntModel].vtxMin.z = vtx.z;
			}

			g_Santa.aModel[nCntModel].pVtxBuff += g_Santa.aModel[nCntModel].sizeFVF;
		}

		g_Santa.aModel[nCntModel].vtxMinDef = g_Santa.aModel[nCntModel].vtxMin;
		g_Santa.aModel[nCntModel].vtxMaxDef = g_Santa.aModel[nCntModel].vtxMax;
	}

	g_Santa.aModel[0].nIdxModelParent = -1;
	g_Santa.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Santa.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Santa.aModel[0].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	for (int nCnt = 0; nCnt < MAX_MODEL_SANTA; nCnt++)
	{
		g_Santa.aModel[nCnt].posDef = g_Santa.aModel[nCnt].pos;
	}

	g_Santa.nIdxShadow = SetShadow(g_Santa.pos, g_Santa.rot);
}

//-------------------
//�|���S���I������
//-------------------
void UninitSanta(void)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_MODEL_SANTA; nCntModel++)
	{
		for (unsigned int i = 0; i < g_Santa.aModel[nCntModel].dwNumMat; i++)
		{
			if (g_Santa.aModel[nCntModel].apTexture[i] != NULL)
			{
				g_Santa.aModel[nCntModel].apTexture[i]->Release();
				g_Santa.aModel[nCntModel].apTexture[i] = NULL;
			}
		}
		//���b�V���̔j��
		if (g_Santa.aModel[nCntModel].pMesh != NULL)
		{
			g_Santa.aModel[nCntModel].pMesh->Release();
			g_Santa.aModel[nCntModel].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_Santa.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Santa.aModel[nCntModel].pBuffMat->Release();
			g_Santa.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateSanta(void)
{
	if (g_Santa.bUse)
	{
		//�ړ�����
		Bed* pBed;
		float Oldrot;//���̕���
		float Xlong;
		float Zlong;
		float Destrot;//�x�b�g�̕���
		if (g_Santa.bPresent)
		{
			//�ړ�����
			Oldrot = atan2f(g_Santa.move.x, g_Santa.move.z);//���̕���
			Xlong = g_Santa.Startpos.x - g_Santa.pos.x;
			Zlong = g_Santa.Startpos.z - g_Santa.pos.z;
			Destrot = atan2f(Xlong, Zlong);//�x�b�g�̕���

			if (sqrtf(Xlong * Xlong + Zlong * Zlong) < PRESENT_SPACE)
			{
				EndSanta();
			}
		}
		else
		{
			//�ړ�����
			pBed = GetBed();
			Oldrot = atan2f(g_Santa.move.x, g_Santa.move.z);//���̕���
			Xlong = pBed->pos.x - g_Santa.pos.x;
			Zlong = pBed->pos.z + pBed->vtxMax.z - g_Santa.pos.z;
			Destrot = atan2f(Xlong, Zlong);//�x�b�g�̕���

			if (sqrtf(Xlong * Xlong + Zlong * Zlong) < PRESENT_SPACE)
			{
				g_Santa.bPresent = true;
			}
			SetPresentPos(g_Santa.pos);
		}

		float Diffrot = Destrot - Oldrot;//���̊p�x
		if (Diffrot > D3DX_PI)
		{//�C��
			Diffrot -= D3DX_PI * 2;
		}
		else if (Diffrot < -D3DX_PI)
		{//�C��
			Diffrot += D3DX_PI * 2;
		}

		Oldrot += Diffrot * 1.0f;//�p�x��␳

		if (Oldrot > D3DX_PI)
		{//�C��
			Oldrot -= D3DX_PI * 2;
		}
		else if (Oldrot < -D3DX_PI)
		{//�C��
			Oldrot += D3DX_PI * 2;
		}

		g_Santa.move.x += sinf(Oldrot) * SANTA_SPEED;
		g_Santa.move.z += cosf(Oldrot) * SANTA_SPEED;
		g_Santa.Destrot.y = Oldrot - D3DX_PI;
		if (g_Santa.motionType != MOTIONTYPE_JUMP && g_Santa.motionType != MOTIONTYPE_LANDING && g_Santa.motionType != MOTIONTYPE_ACTION)
		{
			g_Santa.motionType = MOTIONTYPE_MOVE;
		}

		g_Santa.move.y += GRAVITY;

		g_Santa.posOld = g_Santa.pos;

		//�ʒu�̍X�V
		g_Santa.pos.x += g_Santa.move.x;
		g_Santa.pos.y += g_Santa.move.y;
		g_Santa.pos.z += g_Santa.move.z;

		//�ړ��ʂ̍X�V(����)
		g_Santa.move.x += (SANTA_SPEED_DEF - g_Santa.move.x) * SANTA_INA;
		g_Santa.move.z += (SANTA_SPEED_DEF - g_Santa.move.z) * SANTA_INA;

		g_Santa.pStage = NULL;

		CollisionStage(&g_Santa.pStage);

		if (g_Santa.pStage != NULL)
		{
			g_Santa.pos += g_Santa.pStage->move;
		}

		if (g_Santa.pos.x < -GAME_WALL)
		{
			g_Santa.pos.x = -GAME_WALL;
		}
		if (g_Santa.pos.x > GAME_WALL)
		{
			g_Santa.pos.x = GAME_WALL;
		}
		if (g_Santa.pos.z < -GAME_WALL)
		{
			g_Santa.pos.z = -GAME_WALL;
		}
		if (g_Santa.pos.z > GAME_WALL)
		{
			g_Santa.pos.z = GAME_WALL;
		}

		if (sqrtf(g_Santa.move.x * g_Santa.move.x + g_Santa.move.z * g_Santa.move.z) < 1.0f && g_Santa.motionType == MOTIONTYPE_MOVE)
		{
			g_Santa.move.x = 0.0f;
			g_Santa.move.z = 0.0f;
			g_Santa.motionType = MOTIONTYPE_NEUTRAL;
		}

		//���K��
		if (g_Santa.Destrot.y > D3DX_PI)
		{
			g_Santa.Destrot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.Destrot.y < -D3DX_PI)
		{
			g_Santa.Destrot.y += D3DX_PI * 2.0f;
		}

		//���K��
		if (g_Santa.Destrot.y - g_Santa.rot.y > D3DX_PI)
		{
			g_Santa.Destrot.y = g_Santa.rot.y + ((g_Santa.Destrot.y - g_Santa.rot.y) - D3DX_PI * 2.0f);
		}
		else if (g_Santa.Destrot.y - g_Santa.rot.y < -D3DX_PI)
		{
			g_Santa.Destrot.y = g_Santa.rot.y + ((g_Santa.Destrot.y - g_Santa.rot.y) + D3DX_PI * 2.0f);
		}

		g_Santa.rot.y += (g_Santa.Destrot.y - g_Santa.rot.y) * SANTA_ROT_SPEED;

		//���K��
		if (g_Santa.rot.y > D3DX_PI)
		{
			g_Santa.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.rot.y < -D3DX_PI)
		{
			g_Santa.rot.y += D3DX_PI * 2.0f;
		}

		//���K��
		if (g_Santa.Destrot.x > D3DX_PI)
		{
			g_Santa.Destrot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.Destrot.x < -D3DX_PI)
		{
			g_Santa.Destrot.x += D3DX_PI * 2.0f;
		}

		//���K��
		if (g_Santa.Destrot.x - g_Santa.rot.x > D3DX_PI)
		{
			g_Santa.Destrot.x = g_Santa.rot.x + ((g_Santa.Destrot.x - g_Santa.rot.x) - D3DX_PI * 2.0f);
		}
		else if (g_Santa.Destrot.x - g_Santa.rot.x < -D3DX_PI)
		{
			g_Santa.Destrot.x = g_Santa.rot.x + ((g_Santa.Destrot.x - g_Santa.rot.x) + D3DX_PI * 2.0f);
		}

		g_Santa.rot.x += (g_Santa.Destrot.x - g_Santa.rot.x) * SANTA_ROT_SPEED;

		//���K��
		if (g_Santa.rot.x > D3DX_PI)
		{
			g_Santa.rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.rot.x < -D3DX_PI)
		{
			g_Santa.rot.x += D3DX_PI * 2.0f;
		}

		//�X�P�[������
		g_Santa.scale.x = max(SANTA_SCALE_MIN, min(SANTA_SCALE_MAX, g_Santa.scale.x));
		g_Santa.scale.y = max(SANTA_SCALE_MIN, min(SANTA_SCALE_MAX, g_Santa.scale.y));
		g_Santa.scale.z = max(SANTA_SCALE_MIN, min(SANTA_SCALE_MAX, g_Santa.scale.z));

		int nCntModel;
		//�p�[�c����
		for (nCntModel = 0; nCntModel < g_Santa.nNumModel; nCntModel++)
		{
			g_Santa.aModel[nCntModel].vtxMax.x = g_Santa.aModel[nCntModel].vtxMaxDef.x * g_Santa.scale.x;
			g_Santa.aModel[nCntModel].vtxMax.y = g_Santa.aModel[nCntModel].vtxMaxDef.y * g_Santa.scale.y;
			g_Santa.aModel[nCntModel].vtxMax.z = g_Santa.aModel[nCntModel].vtxMaxDef.z * g_Santa.scale.z;
			g_Santa.aModel[nCntModel].vtxMin.x = g_Santa.aModel[nCntModel].vtxMinDef.x * g_Santa.scale.x;
			g_Santa.aModel[nCntModel].vtxMin.y = g_Santa.aModel[nCntModel].vtxMinDef.y * g_Santa.scale.y;
			g_Santa.aModel[nCntModel].vtxMin.z = g_Santa.aModel[nCntModel].vtxMinDef.z * g_Santa.scale.z;
		}

		//UpdateSantaMotion();

		switch (g_Santa.state)
		{
		case SANTASTATE_APPEAR:
			g_Santa.bUse = false;
			break;
		case SANTASTATE_NORMAL:
			if (g_Santa.nLife <= 0)
			{
				g_Santa.state = SANTASTATE_DIE;
			}
			SetPositionShadow(g_Santa.nIdxShadow, g_Santa.pos, g_Santa.scale, 200.0f);
			SetLife(g_Santa.pos + D3DXVECTOR3(0.0f, LIFE_SPACE, 0.0f), (float)((float)g_Santa.nLife / (float)SANTA_LIFE), g_Santa.nIdxLife);
			break;
		case SANTASTATE_DIE:
			g_Santa.Destrot.x = D3DX_PI * 0.5f;
			static int nCnt = 0;
			nCnt++;
			if (nCnt >= 20)
			{
				NullShadow(g_Santa.nIdxShadow);
				NullLife(g_Santa.nIdxLife);
				SetParticle(g_Santa.pos, g_Santa.scale);
				g_Santa.state = SANTASTATE_APPEAR;
			}
			break;
		}
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawSanta(void)
{
	if (g_Santa.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
		D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^


		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//�}�g���b�N�X������
		D3DXMatrixIdentity(&g_Santa.mtxWorld);

		//�傫���̔��f
		D3DXMatrixScaling(&mtxScale, g_Santa.scale.x, g_Santa.scale.y, g_Santa.scale.z);
		D3DXMatrixMultiply(&g_Santa.mtxWorld, &g_Santa.mtxWorld, &mtxScale);

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Santa.rot.y, g_Santa.rot.x, g_Santa.rot.z);
		D3DXMatrixMultiply(&g_Santa.mtxWorld, &g_Santa.mtxWorld, &mtxRot);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, g_Santa.pos.x, g_Santa.pos.y, g_Santa.pos.z);
		D3DXMatrixMultiply(&g_Santa.mtxWorld, &g_Santa.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Santa.mtxWorld);

		int nCntModel;
		//�p�[�c����
		for (nCntModel = 0; nCntModel < g_Santa.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//�v�Z�}�g���b�N�X
			D3DXMATRIX mtxParent;
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_Santa.aModel[nCntModel].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScaleModel, g_Santa.aModel[nCntModel].scale.x, g_Santa.aModel[nCntModel].scale.y, g_Santa.aModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_Santa.aModel[nCntModel].mtxWorld, &g_Santa.aModel[nCntModel].mtxWorld, &mtxScaleModel);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Santa.aModel[nCntModel].rot.y, g_Santa.aModel[nCntModel].rot.x, g_Santa.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Santa.aModel[nCntModel].mtxWorld, &g_Santa.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//�ʒu�̔��f
			D3DXMatrixTranslation(&mtxTransModel, g_Santa.aModel[nCntModel].pos.x, g_Santa.aModel[nCntModel].pos.y, g_Santa.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_Santa.aModel[nCntModel].mtxWorld, &g_Santa.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
			if (g_Santa.aModel[nCntModel].nIdxModelParent != -1)
			{//�e���f��������
				mtxParent = g_Santa.aModel[g_Santa.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//�e���f�����Ȃ�
				mtxParent = g_Santa.mtxWorld;
			}

			D3DXMatrixMultiply(&g_Santa.aModel[nCntModel].mtxWorld, &g_Santa.aModel[nCntModel].mtxWorld, &mtxParent);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Santa.aModel[nCntModel].mtxWorld);

			//���݂̃}�e���A���擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Santa.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Santa.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//�e�N�X�`��
				pDevice->SetTexture(0, g_Santa.aModel[nCntModel].apTexture[nCntMat]);

				//���f���`��
				g_Santa.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------
//�o��
//-----------------------------
void SetSanta(D3DXVECTOR3 pos)
{
	g_Santa.pos = pos;
	g_Santa.posOld = pos;
	g_Santa.Startpos = pos;
	g_Santa.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Santa.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Santa.Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Santa.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Santa.nLife = SANTA_LIFE;
	g_Santa.state = SANTASTATE_NORMAL;
	g_Santa.nIdxShadow = SetShadow(g_Santa.pos, g_Santa.rot);
	g_Santa.nIdxLife = LinkLife();
	g_Santa.pStage = NULL;

	g_Santa.bLoopMotion = false;
	g_Santa.motionType = MOTIONTYPE_NEUTRAL;
	g_Santa.nCounterMotion = 0;
	g_Santa.nKey = -1;
	g_Santa.nNumKey = 0;
	g_Santa.nNumMotion = NUM_MOTION_SANTA;
	g_Santa.bPresent = false;
	g_Santa.bUse = true;
}

//-----------------------------
//�j��
//-----------------------------
void EndSanta(void)
{
	g_Santa.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Santa.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Santa.Startpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Santa.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Santa.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Santa.Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Santa.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Santa.nLife = SANTA_LIFE;
	g_Santa.state = SANTASTATE_NORMAL;
	NullShadow(g_Santa.nIdxShadow);
	g_Santa.nIdxShadow = -1;
	NullLife(g_Santa.nIdxLife);
	g_Santa.nIdxLife = -1;
	g_Santa.pStage = NULL;

	g_Santa.bLoopMotion = false;
	g_Santa.motionType = MOTIONTYPE_NEUTRAL;
	g_Santa.nCounterMotion = 0;
	g_Santa.nKey = -1;
	g_Santa.nNumKey = 0;
	g_Santa.nNumMotion = NUM_MOTION_SANTA;
	g_Santa.bPresent = false;
	g_Santa.bUse = false;
}

//------------------------------
//�ʒu�擾
//------------------------------
Santa* GetSanta(void)
{
	return &g_Santa;
}

//------------------------------
//���[�V����
//------------------------------
void UpdateSantaMotion(void)
{
	static MOTIONTYPE OldMotion = MOTIONTYPE_NEUTRAL;
	static int BlendCnt = 0;
	if (OldMotion != g_Santa.motionType)
	{
		g_Santa.aMotionInfo[OldMotion] = g_SantaMotion[OldMotion];
		g_Santa.aMotionInfo[g_Santa.motionType] = g_SantaMotion[g_Santa.motionType];

		for (int nCntModel = 0; nCntModel < g_Santa.nNumModel; nCntModel++)
		{
			D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_Santa.aMotionInfo[OldMotion].aKeyInfo[g_Santa.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosX, g_Santa.aMotionInfo[OldMotion].aKeyInfo[g_Santa.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosY, g_Santa.aMotionInfo[OldMotion].aKeyInfo[g_Santa.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 Destpos = D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[0].aKey[nCntModel].fPosX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[0].aKey[nCntModel].fPosY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[0].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 posDif = Destpos - Oldpos;

			D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_Santa.aMotionInfo[OldMotion].aKeyInfo[g_Santa.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotX, g_Santa.aMotionInfo[OldMotion].aKeyInfo[g_Santa.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotY, g_Santa.aMotionInfo[OldMotion].aKeyInfo[g_Santa.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotZ);
			D3DXVECTOR3 Destrot = D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[0].aKey[nCntModel].fRotX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[0].aKey[nCntModel].fRotY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[0].aKey[nCntModel].fRotZ);

			//���K��
			if (Destrot.x - Oldrot.x > D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
			}
			else if (Destrot.x - Oldrot.x < -D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
			}
			//���K��
			if (Destrot.y - Oldrot.y > D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
			}
			else if (Destrot.y - Oldrot.y < -D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
			}
			//���K��
			if (Destrot.z - Oldrot.z > D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
			}
			else if (Destrot.z - Oldrot.z < -D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
			}

			D3DXVECTOR3 rotDif = Destrot - Oldrot;

			g_Santa.aModel[nCntModel].pos = g_Santa.aModel[nCntModel].posDef + Oldpos + posDif * (BlendCnt / SANTA_BLEND_FRAME);
			g_Santa.aModel[nCntModel].rot = Oldrot + rotDif * (BlendCnt / SANTA_BLEND_FRAME);

			//���K��
			if (g_Santa.aModel[nCntModel].rot.x > D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_Santa.aModel[nCntModel].rot.x < -D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			//���K��
			if (g_Santa.aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Santa.aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			//���K��
			if (g_Santa.aModel[nCntModel].rot.z > D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
			else if (g_Santa.aModel[nCntModel].rot.z < -D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
		}

		if (BlendCnt == (int)SANTA_BLEND_FRAME)
		{
			BlendCnt = 0;
			OldMotion = g_Santa.motionType;
			return;
		}
		BlendCnt++;
		return;
	}
	g_Santa.aMotionInfo[g_Santa.motionType] = g_SantaMotion[g_Santa.motionType];
	g_Santa.nNumKey = g_Santa.aMotionInfo[g_Santa.motionType].nNumKey;
	g_Santa.bLoopMotion = g_Santa.aMotionInfo[g_Santa.motionType].bLoop;
	static int nDestKey = g_Santa.nKey + 1;

	if (g_Santa.nCounterMotion >= g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].nFrame)
	{
		g_Santa.nCounterMotion = 0;
	}

	if (g_Santa.nCounterMotion == 0)
	{
		if (nDestKey >= g_Santa.nNumKey - 1)
		{
			if (g_Santa.bLoopMotion)
			{
				g_Santa.nKey++;
				nDestKey = 0;

				for (int nCntModel = 0; nCntModel < g_Santa.nNumModel; nCntModel++)
				{
					g_Santa.aModel[nCntModel].pos = g_Santa.aModel[nCntModel].posDef + D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fPosX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fPosY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fPosZ);
					g_Santa.aModel[nCntModel].rot = D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fRotX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fRotY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fRotZ);
				}
			}
			else
			{
				g_Santa.nKey = -1;
				nDestKey = g_Santa.nKey + 1;
				g_Santa.motionType = MOTIONTYPE_NEUTRAL;
				return;
			}
		}
		else
		{
			g_Santa.nKey++;
			if (g_Santa.nKey > g_Santa.nNumKey - 1)
			{
				g_Santa.nKey = 0;
			}
			nDestKey = g_Santa.nKey + 1;

			for (int nCntModel = 0; nCntModel < g_Santa.nNumModel; nCntModel++)
			{
				g_Santa.aModel[nCntModel].pos = g_Santa.aModel[nCntModel].posDef + D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fPosX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fPosY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fPosZ);
				g_Santa.aModel[nCntModel].rot = D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fRotX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fRotY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fRotZ);
			}
		}
	}

	for (int nCntModel = 0; nCntModel < g_Santa.nNumModel; nCntModel++)
	{
		D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fPosX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fPosY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 Destpos = D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 posDif = Destpos - Oldpos;

		D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fRotX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fRotY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].aKey[nCntModel].fRotZ);
		D3DXVECTOR3 Destrot = D3DXVECTOR3(g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotX, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotY, g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotZ);

		//���K��
		if (Destrot.x - Oldrot.x > D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
		}
		else if (Destrot.x - Oldrot.x < -D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
		}
		//���K��
		if (Destrot.y - Oldrot.y > D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
		}
		else if (Destrot.y - Oldrot.y < -D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
		}
		//���K��
		if (Destrot.z - Oldrot.z > D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
		}
		else if (Destrot.z - Oldrot.z < -D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
		}

		D3DXVECTOR3 rotDif = Destrot - Oldrot;

		g_Santa.aModel[nCntModel].pos = g_Santa.aModel[nCntModel].posDef + Oldpos + posDif * (g_Santa.nCounterMotion / (float)g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].nFrame);
		g_Santa.aModel[nCntModel].rot = Oldrot + rotDif * (g_Santa.nCounterMotion / (float)g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].nFrame);

		//���K��
		if (g_Santa.aModel[nCntModel].rot.x > D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.aModel[nCntModel].rot.x < -D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		//���K��
		if (g_Santa.aModel[nCntModel].rot.y > D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.aModel[nCntModel].rot.y < -D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}
		//���K��
		if (g_Santa.aModel[nCntModel].rot.z > D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.aModel[nCntModel].rot.z < -D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
	g_Santa.nCounterMotion++;
}

//------------------------------------------------
//�Փ�
//------------------------------------------------
void CollisionSanta(D3DXVECTOR3 pos, float Length)
{
	float Space = sqrtf((pos.x - g_Santa.pos.x) * (pos.x - g_Santa.pos.x) + (pos.y - g_Santa.pos.y) * (pos.y - g_Santa.pos.y) + (pos.z - g_Santa.pos.z) * (pos.z - g_Santa.pos.z));
	if (Space < SANTA_SIZE * 0.5f + Length * 0.5f)
	{
		Space = (SANTA_SIZE * 0.5f + Length * 0.5f) - Space;
		D3DXVECTOR3 Hitvec = g_Santa.pos - pos;
		D3DXVec3Normalize(&Hitvec, &Hitvec);
		g_Santa.move += Hitvec * Space;
	}
}