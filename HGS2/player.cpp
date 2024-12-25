//----------------------------------------
//
//���f���\������[player.cpp]
//Author fuma sato
//
//----------------------------------------

//****************************************
// �C���N���[�h�t�@�C��
//****************************************
#include"player.h"
#include"game.h"
#include"shadow.h"
#include"camera.h"
#include"input.h"
#include"bullet.h"
#include"file.h"
#include"particle.h"
#include"life.h"
#include"snowball.h"

//****************************************
// �}�N����`
//****************************************
#define MAX_WORD (128) // �ő�̕�����

//****************************************
// �O���[�o���ϐ�
//****************************************
Player g_Player;

static MOTION_INFO g_Motion[] =
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
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.bJump = false;
	g_Player.nLife = PLAYER_LIFE;
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.nIdxShadow = -1;
	g_Player.nIdxLife = -1;
	g_Player.pStage = NULL;

	g_Player.bLoopMotion = false;
	g_Player.motionType = MOTIONTYPE_NEUTRAL;
	g_Player.nCounterMotion = 0;
	g_Player.nKey = -1;
	g_Player.nNumKey = 0;
	g_Player.nNumMotion = NUM_MOTION;
	g_Player.bUse = true;

	LoadModel();
	LoadPlayer();

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_BODY_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[0].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[0].dwNumMat,
	//	&g_Player.aModel[0].pMesh
	//);

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_HEAD_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[1].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[1].dwNumMat,
	//	&g_Player.aModel[1].pMesh
	//);

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_RIGHTARM_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[2].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[2].dwNumMat,
	//	&g_Player.aModel[2].pMesh
	//);

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_RIGHTHAND_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[3].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[3].dwNumMat,
	//	&g_Player.aModel[3].pMesh
	//);

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_LEFTARM_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[4].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[4].dwNumMat,
	//	&g_Player.aModel[4].pMesh
	//);

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_LEFTHAND_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[5].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[5].dwNumMat,
	//	&g_Player.aModel[5].pMesh
	//);

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_RIGHTLEG_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[6].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[6].dwNumMat,
	//	&g_Player.aModel[6].pMesh
	//);

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_RIGHTFOOT_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[7].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[7].dwNumMat,
	//	&g_Player.aModel[7].pMesh
	//);

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_LEFTLEG_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[8].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[8].dwNumMat,
	//	&g_Player.aModel[8].pMesh
	//);

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX
	//(
	//	PLAYER_LEFTFOOT_NAME,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[9].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[9].dwNumMat,
	//	&g_Player.aModel[9].pMesh
	//);

	//g_Player.nNumModel = NUM_MODEL;

	int nCntModel;

	for (nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`��������
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Player.aModel[nCntModel].apTexture[nCntMat]
				);
			}
		}

		//���_��
		g_Player.aModel[nCntModel].nNumVtx = g_Player.aModel[nCntModel].pMesh->GetNumVertices();
		//���_�T�C�Y
		g_Player.aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMesh->GetFVF());
		//���_�o�b�t�@�̎擾
		g_Player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Player.aModel[nCntModel].pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < g_Player.aModel[nCntModel].nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Player.aModel[nCntModel].pVtxBuff;

			if (vtx.x > g_Player.aModel[nCntModel].vtxMax.x)
			{
				g_Player.aModel[nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.x < g_Player.aModel[nCntModel].vtxMin.x)
			{
				g_Player.aModel[nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y > g_Player.aModel[nCntModel].vtxMax.y)
			{
				g_Player.aModel[nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.y < g_Player.aModel[nCntModel].vtxMin.y)
			{
				g_Player.aModel[nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z > g_Player.aModel[nCntModel].vtxMax.z)
			{
				g_Player.aModel[nCntModel].vtxMax.z = vtx.z;
			}
			if (vtx.z < g_Player.aModel[nCntModel].vtxMin.z)
			{
				g_Player.aModel[nCntModel].vtxMin.z = vtx.z;
			}

			g_Player.aModel[nCntModel].pVtxBuff += g_Player.aModel[nCntModel].sizeFVF;
		}

		g_Player.aModel[nCntModel].vtxMinDef = g_Player.aModel[nCntModel].vtxMin;
		g_Player.aModel[nCntModel].vtxMaxDef = g_Player.aModel[nCntModel].vtxMax;
	}

	//�S���f���̑傫����ݒ肷��
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		g_Player.aModel[nCntModel].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//�傫����ݒ�
	}

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		g_Player.aModel[nCnt].posDef = g_Player.aModel[nCnt].pos;
	}

	g_Player.nIdxShadow = SetShadow(g_Player.pos, g_Player.rot);
	g_Player.nIdxLife = LinkLife();
}

//-------------------
//�|���S���I������
//-------------------
void UninitPlayer(void)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		for (unsigned int i = 0; i < g_Player.aModel[nCntModel].dwNumMat; i++)
		{
			if (g_Player.aModel[nCntModel].apTexture[i] != NULL)
			{
				g_Player.aModel[nCntModel].apTexture[i]->Release();
				g_Player.aModel[nCntModel].apTexture[i] = NULL;
			}
		}
		//���b�V���̔j��
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdatePlayer(void)
{
	if (g_Player.bUse)
	{
		Camera* pCamera = GetCamera();
		float* pStick;

		//�ړ�����

		//X
		if (IsXInputControllerConnected(CONTROLLER_1))
		{
			//���X�e�B�b�N����
			pStick = GetJoyStick(STICK_LEFT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f + -atan2f(*(pStick + 1), *pStick);
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		//d
		else if (IsDirectInputControllerConnected(CONTROLLER_1))
		{

			//���X�e�B�b�N����
			pStick = GetdJoyStick(STICK_LEFT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f + atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f + atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f + atan2f(*(pStick + 1), *pStick);
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}

		if (GetKeyboradPress(DIK_A) == true || GetJoykeyPress(JOYKEY_LEFT, CONTROLLER_1) == true)//A�L�[
		{
			if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//W�L�[
			{//����
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.75f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//S�L�[
			{//����
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.25f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else
			{//��
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.5f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		else if (GetKeyboradPress(DIK_D) == true || GetJoykeyPress(JOYKEY_RIGHT, CONTROLLER_1) == true)//D�L�[
		{
			if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//W�L�[
			{//�E��
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.75f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//S�L�[
			{//�E��
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.25f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else
			{//�E
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		else if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//W�L�[
		{//��
			g_Player.move.x += sinf(pCamera->rot.y) * SPEED;
			g_Player.move.z += cosf(pCamera->rot.y) * SPEED;
			g_Player.Destrot.y = pCamera->rot.y + D3DX_PI;
			if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
			{
				g_Player.motionType = MOTIONTYPE_MOVE;
			}
		}
		else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//S�L�[
		{//��
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI) * SPEED;
			g_Player.Destrot.y = pCamera->rot.y;
			if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
			{
				g_Player.motionType = MOTIONTYPE_MOVE;
			}
		}

		if (GetKeyboradTrigger(DIK_SPACE) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_1) == true)//S�L�[
		{//��
			if (!g_Player.bJump)
			{
				g_Player.move.y += JUMP;
				g_Player.bJump = true;
				g_Player.motionType = MOTIONTYPE_JUMP;
			}
		}

		if (GetKeyboradTrigger(DIK_RETURN) == true || GetMouseTrigger(MOUSE_LEFT) == true || GetJoykeyTrigger(JOYKEY_X, CONTROLLER_1) == true)
		{
			g_Player.motionType = MOTIONTYPE_ACTION;
		}

		if (!IsXInputControllerConnected(CONTROLLER_1) && IsDirectInputControllerConnected(CONTROLLER_1))
		{
			if (GetdJoyPov(POV_UP, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_RIGHTUP, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.75f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_RIGHT, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_RIGHTDOWN, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.25f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_DOWN, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_LEFTDOWN, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.25f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_LEFT, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.5f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_LEFTUP, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.75f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}

		if (!strcmp(ControllerName(CONTROLLER_1), ELE_CON))
		{
			if (GetdJoykeyPress(ELEKEY_A, CONTROLLER_1) == true)
			{//��
				if (!g_Player.bJump)
				{
					g_Player.move.y += JUMP;
					g_Player.bJump = true;
					g_Player.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(ELEKEY_X, CONTROLLER_1) == true)
			{
				g_Player.motionType = MOTIONTYPE_ACTION;
			}
		}
		else if (!strcmp(ControllerName(CONTROLLER_1), PS_CON))
		{
			if (GetdJoykeyPress(PSKEY_CR, CONTROLLER_1) == true)
			{//��
				if (!g_Player.bJump)
				{
					g_Player.move.y += JUMP;
					g_Player.bJump = true;
					g_Player.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(PSKEY_SQ, CONTROLLER_1) == true)
			{
				g_Player.motionType = MOTIONTYPE_ACTION;
			}
		}
		else if (!strcmp(ControllerName(CONTROLLER_1), NIN_CON))
		{
			if (GetdJoykeyPress(NINKEY_B, CONTROLLER_1) == true)
			{//��
				if (!g_Player.bJump)
				{
					g_Player.move.y += JUMP;
					g_Player.bJump = true;
					g_Player.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(NINKEY_Y, CONTROLLER_1) == true)
			{
				g_Player.motionType = MOTIONTYPE_ACTION;
			}
		}
		else if (!IsXInputControllerConnected(CONTROLLER_1) && IsDirectInputControllerConnected(CONTROLLER_1))
		{
			if (GetdJoykeyPress(DKEY_A, CONTROLLER_1) == true)
			{//��
				if (!g_Player.bJump)
				{
					g_Player.move.y += JUMP;
					g_Player.bJump = true;
					g_Player.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(DKEY_X, CONTROLLER_1) == true)
			{
				g_Player.motionType = MOTIONTYPE_ACTION;
			}
		}

		g_Player.move.y += GRAVITY;

		if (g_Player.bJump)
		{
			g_Player.move.x *= JUMP_INA;
			g_Player.move.z *= JUMP_INA;
		}

		g_Player.posOld = g_Player.pos;

		//if (g_Player.motionType == MOTIONTYPE_ACTION)
		//{
		//	g_Player.move.x = 0.0f;
		//	g_Player.move.z = 0.0f;
		//}

		//�ʒu�̍X�V
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;
		g_Player.pos.z += g_Player.move.z;

		//�ړ��ʂ̍X�V(����)
		g_Player.move.x += (SPEED_DEF - g_Player.move.x) * PLAYER_INA;
		g_Player.move.z += (SPEED_DEF - g_Player.move.z) * PLAYER_INA;

		g_Player.pStage = NULL;

		CollisionSnowBall(g_Player.pos, PLAYER_SIZE);

		g_Player.bJump = !CollisionStage(&g_Player.pStage);

		if (g_Player.pStage != NULL)
		{
			g_Player.pos += g_Player.pStage->move;
		}

		if (g_Player.pos.x < -GAME_WALL)
		{
			g_Player.pos.x = -GAME_WALL;
		}
		if (g_Player.pos.x > GAME_WALL)
		{
			g_Player.pos.x = GAME_WALL;
		}
		if (g_Player.pos.z < -GAME_WALL)
		{
			g_Player.pos.z = -GAME_WALL;
		}
		if (g_Player.pos.z > GAME_WALL)
		{
			g_Player.pos.z = GAME_WALL;
		}

		if (sqrtf(g_Player.move.x * g_Player.move.x + g_Player.move.z * g_Player.move.z) < 0.1f && g_Player.motionType == MOTIONTYPE_MOVE)
		{
			g_Player.move.x = 0.0f;
			g_Player.move.z = 0.0f;
			g_Player.motionType = MOTIONTYPE_NEUTRAL;
		}

		//���K��
		if (g_Player.Destrot.y > D3DX_PI)
		{
			g_Player.Destrot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player.Destrot.y < -D3DX_PI)
		{
			g_Player.Destrot.y += D3DX_PI * 2.0f;
		}

		//���K��
		if (g_Player.Destrot.y - g_Player.rot.y > D3DX_PI)
		{
			g_Player.Destrot.y = g_Player.rot.y + ((g_Player.Destrot.y - g_Player.rot.y) - D3DX_PI * 2.0f);
		}
		else if (g_Player.Destrot.y - g_Player.rot.y < -D3DX_PI)
		{
			g_Player.Destrot.y = g_Player.rot.y + ((g_Player.Destrot.y - g_Player.rot.y) + D3DX_PI * 2.0f);
		}

		g_Player.rot.y += (g_Player.Destrot.y - g_Player.rot.y) * ROT_SPEED;

		//���K��
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += D3DX_PI * 2.0f;
		}

		//���K��
		if (g_Player.Destrot.x > D3DX_PI)
		{
			g_Player.Destrot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Player.Destrot.x < -D3DX_PI)
		{
			g_Player.Destrot.x += D3DX_PI * 2.0f;
		}

		//���K��
		if (g_Player.Destrot.x - g_Player.rot.x > D3DX_PI)
		{
			g_Player.Destrot.x = g_Player.rot.x + ((g_Player.Destrot.x - g_Player.rot.x) - D3DX_PI * 2.0f);
		}
		else if (g_Player.Destrot.x - g_Player.rot.x < -D3DX_PI)
		{
			g_Player.Destrot.x = g_Player.rot.x + ((g_Player.Destrot.x - g_Player.rot.x) + D3DX_PI * 2.0f);
		}

		g_Player.rot.x += (g_Player.Destrot.x - g_Player.rot.x) * ROT_SPEED;

		//���K��
		if (g_Player.rot.x > D3DX_PI)
		{
			g_Player.rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Player.rot.x < -D3DX_PI)
		{
			g_Player.rot.x += D3DX_PI * 2.0f;
		}

		//�X�P�[������
		g_Player.scale.x = max(SCALE_MIN, min(SCALE_MAX, g_Player.scale.x));
		g_Player.scale.y = max(SCALE_MIN, min(SCALE_MAX, g_Player.scale.y));
		g_Player.scale.z = max(SCALE_MIN, min(SCALE_MAX, g_Player.scale.z));

		int nCntModel;
		//�p�[�c����
		for (nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			g_Player.aModel[nCntModel].vtxMax.x = g_Player.aModel[nCntModel].vtxMaxDef.x * g_Player.scale.x;
			g_Player.aModel[nCntModel].vtxMax.y = g_Player.aModel[nCntModel].vtxMaxDef.y * g_Player.scale.y;
			g_Player.aModel[nCntModel].vtxMax.z = g_Player.aModel[nCntModel].vtxMaxDef.z * g_Player.scale.z;
			g_Player.aModel[nCntModel].vtxMin.x = g_Player.aModel[nCntModel].vtxMinDef.x * g_Player.scale.x;
			g_Player.aModel[nCntModel].vtxMin.y = g_Player.aModel[nCntModel].vtxMinDef.y * g_Player.scale.y;
			g_Player.aModel[nCntModel].vtxMin.z = g_Player.aModel[nCntModel].vtxMinDef.z * g_Player.scale.z;
		}

		UpdateMotion();

		switch (g_Player.state)
		{
		case PLAYERSTATE_APPEAR:
			g_Player.bUse = false;
			break;
		case PLAYERSTATE_NORMAL:
			if (g_Player.nLife <= 0)
			{
				g_Player.state = PLAYERSTATE_DIE;
			}
			SetPositionShadow(g_Player.nIdxShadow, g_Player.pos, g_Player.scale, 200.0f);
			SetLife(g_Player.pos + g_Player.aModel[0].pos + g_Player.aModel[1].pos + g_Player.aModel[10].pos, (float)((float)g_Player.nLife / (float)PLAYER_LIFE), g_Player.nIdxLife);
			break;
		case PLAYERSTATE_DIE:
			g_Player.Destrot.x = D3DX_PI * 0.5f;
			static int nCnt = 0;
			nCnt++;
			if (nCnt >= 20)
			{
				NullShadow(g_Player.nIdxShadow);
				NullLife(g_Player.nIdxLife);
				SetParticle(g_Player.pos, g_Player.scale);
				g_Player.state = PLAYERSTATE_APPEAR;
			}
			break;
		}
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawPlayer(void)
{
	if (g_Player.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
		D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^


		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//�}�g���b�N�X������
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		//�傫���̔��f
		D3DXMatrixScaling(&mtxScale, g_Player.scale.x, g_Player.scale.y, g_Player.scale.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScale);

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

		int nCntModel;
		//�p�[�c����
		for (nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//�v�Z�}�g���b�N�X
			D3DXMATRIX mtxParent;
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScaleModel, g_Player.aModel[nCntModel].scale.x, g_Player.aModel[nCntModel].scale.y, g_Player.aModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxScaleModel);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//�ʒu�̔��f
			D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
			if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
			{//�e���f��������
				mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//�e���f�����Ȃ�
				mtxParent = g_Player.mtxWorld;
			}

			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

			//���݂̃}�e���A���擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//�e�N�X�`��
				pDevice->SetTexture(0, g_Player.aModel[nCntModel].apTexture[nCntMat]);

				//���f���`��
				g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//------------------------------
//�ʒu�擾
//------------------------------
Player* GetPlayer(void)
{
	return &g_Player;
}

//------------------------------
//���[�V����
//------------------------------
void UpdateMotion(void)
{
	int nextKey = 0;//���̃L�[

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		float DiffPosX, DiffPosY, DiffPosZ, DiffRotX, DiffRotY, DiffRotZ; //�ʒu�̍��A�����̍������߂�ϐ�

		DiffPosX = DiffPosY = DiffPosZ = DiffRotX = DiffRotY = DiffRotZ = 0.0f; //�ϐ���������

		nextKey = (g_Player.nKey + 1) % g_Player.aMotionInfo[g_Player.motionType].nNumKey;//���̃L�[���v�Z

		//�ʒu�̍��A�����̍������߂�
		DiffPosX = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fPosX - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX;
		DiffPosY = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fPosY - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY;
		DiffPosZ = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fPosZ - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ;
		DiffRotX = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fRotX - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX;
		DiffRotY = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fRotY - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY;
		DiffRotZ = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fRotZ - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ;

		//�p�[�c�̈ʒuX��ݒ�
		g_Player.aModel[nCntModel].pos.x =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX +
			DiffPosX *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//�p�[�c�̈ʒuY��ݒ�
		g_Player.aModel[nCntModel].pos.y =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY +
			DiffPosY *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//�p�[�c�̈ʒuZ��ݒ�
		g_Player.aModel[nCntModel].pos.z =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ +
			DiffPosZ *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//�p�[�c�̌���X��ݒ�
		g_Player.aModel[nCntModel].rot.x =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX +
			DiffRotX *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//�p�[�c�̌���Y��ݒ�
		g_Player.aModel[nCntModel].rot.y =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY +
			DiffRotY *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//�p�[�c�̌���Z��ݒ�
		g_Player.aModel[nCntModel].rot.z =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ +
			DiffRotZ *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//�I�t�Z�b�g�Ƒ���
		g_Player.aModel[nCntModel].rot += g_Player.aModel[nCntModel].offrot;
		g_Player.aModel[nCntModel].pos += g_Player.aModel[nCntModel].offpos;

		//�J�E���^�[���[�V�������ő�܂ōs������0�ɖ߂�
		if (g_Player.nCounterMotion >= g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame)
		{
			g_Player.nKey = (g_Player.nKey + 1) % g_Player.aMotionInfo[g_Player.motionType].nNumKey;
			g_Player.nCounterMotion = 0;
		}
	}
	g_Player.nCounterMotion++;
}

//------------------------------------------------
//�Փ�
//------------------------------------------------
void CollisionPlayer(D3DXVECTOR3 pos, float Length)
{
	float Space = sqrtf((pos.x - g_Player.pos.x) * (pos.x - g_Player.pos.x) + (pos.y - g_Player.pos.y) * (pos.y - g_Player.pos.y) + (pos.z - g_Player.pos.z) * (pos.z - g_Player.pos.z));
	if (Space < PLAYER_SIZE * 0.5f + Length * 0.5f)
	{
		Space = (PLAYER_SIZE * 0.5f + Length * 0.5f) - Space;
		D3DXVECTOR3 Hitvec = g_Player.pos - pos;
		D3DXVec3Normalize(&Hitvec, &Hitvec);
		g_Player.move += Hitvec * Space;
	}
}
//================================================
// �v���C���[�̓ǂݍ��ݏ���
//================================================
void LoadPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	FILE* pFile;

	int nNumModel = 0;
	int nCnt = 0;
	char skip[3];
	int nIdx = 0;
	int nCntPartsPos = 0;
	int nCntPartsRot = 0;
	int nCntMotion = 0;
	int nKey = 0;

	pFile = fopen(LOADPLAYER, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			char aStr[MAX_WORD];//�����ǂݍ��ݗp�ϐ�

			fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(aStr, "SCRIPT") == 0)
			{//�ǂݎ����������SCRIPT��������

				while (1)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strcmp(aStr, "NUM_MODEL") == 0)
					{
						//�ǂݎ����������NUM_MODEL��������

						fscanf(pFile, "%s", &skip[0]); //[=]��ǂݔ�΂�
						fscanf(pFile, "%d", &nNumModel); //���f���̐���ǂݍ��ޕϐ��ɑ��
					}
					else if (strcmp(aStr, "MODEL_FILENAME") == 0)
					{//�ǂݎ����������MODEL_FILENAME��������

						fscanf(pFile, "%s", &skip[0]);
						fscanf(pFile, "%s", &aStr[0]);

						const char* FILE_NAME = {}; //�t�@�C���̖��O���i�[����ϐ�

						FILE_NAME = aStr; // �ǂݎ�����t�@�C���̖��O����

						//���f����ǂݍ���
						D3DXLoadMeshFromX(FILE_NAME,
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_Player.aModel[nCnt].pBuffMat,
							NULL,
							&g_Player.aModel[nCnt].dwNumMat,
							&g_Player.aModel[nCnt].pMesh);

						nCnt++;//���f���̃J�E���g�𑝂₷
					}
					else if (strcmp(aStr, "CHARACTERSET") == 0)
					{//�ǂݎ����������CHARACTERSET��������
						while (1)
						{
							fscanf(pFile, "%s", &aStr[0]);

							if (strcmp(aStr, "NUM_PARTS") == 0)
							{
								fscanf(pFile, "%s", &skip[0]);

								fscanf(pFile, "%d", &g_Player.nNumModel);
								break;
							}
						}
					}
					else if (strcmp(aStr, "PARTSSET") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aStr[0]);

							if (strcmp(aStr, "INDEX") == 0)
							{
								fscanf(pFile, "%s", &skip[0]);

								fscanf(pFile, "%d", &nIdx);
							}
							else if (strcmp(aStr, "PARENT") == 0)
							{
								fscanf(pFile, "%s", &skip[0]);

								fscanf(pFile, "%d", &g_Player.aModel[nIdx].nIdxModelParent);
							}
							else if (strcmp(aStr, "POS") == 0)
							{
								fscanf(pFile, "%s", &skip[0]);

								fscanf(pFile, "%f", &g_Player.aModel[nIdx].offpos.x);
								fscanf(pFile, "%f", &g_Player.aModel[nIdx].offpos.y);
								fscanf(pFile, "%f", &g_Player.aModel[nIdx].offpos.z);

							}
							else if (strcmp(aStr, "ROT") == 0)
							{
								fscanf(pFile, "%s", &skip[0]);
								fscanf(pFile, "%f", &g_Player.aModel[nIdx].offrot.x);
								fscanf(pFile, "%f", &g_Player.aModel[nIdx].offrot.y);
								fscanf(pFile, "%f", &g_Player.aModel[nIdx].offrot.z);
							}
							else if (strcmp(aStr, "END_PARTSSET") == 0)
							{
								break;
							}
						}
					}
					else if (strcmp(aStr, "MOTIONSET") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aStr[0]);

							if (strcmp(aStr, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &skip[0]);

								fscanf(pFile, "%d", &g_Player.aMotionInfo[nCntMotion].nNumKey);

							}
							else if (strcmp(aStr, "LOOP") == 0)
							{
								fscanf(pFile, "%s", &skip[0]);

								fscanf(pFile, "%d", &g_Player.aMotionInfo[nCntMotion].bLoop);
							}

							if (strcmp(aStr, "KEYSET") == 0)
							{
								while (1)
								{
									fscanf(pFile, "%s", &aStr[0]);

									if (strcmp(aStr, "FRAME") == 0)
									{
										fscanf(pFile, "%s", &skip[0]);

										fscanf(pFile, "%d", &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nKey].nFrame);
									}
									else if (strcmp(aStr, "KEY") == 0)
									{
										while (1)
										{
											fscanf(pFile, "%s", &aStr[0]);

											if (strcmp(aStr, "POS") == 0)
											{
												fscanf(pFile, "%s", &skip[0]);

												fscanf(pFile, "%f", &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nKey].aKey[nCntPartsPos].fPosX);
												fscanf(pFile, "%f", &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nKey].aKey[nCntPartsPos].fPosY);
												fscanf(pFile, "%f", &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nKey].aKey[nCntPartsPos].fPosZ);

												nCntPartsPos++;
											}
											else if (strcmp(aStr, "ROT") == 0)
											{
												fscanf(pFile, "%s", &skip[0]);

												fscanf(pFile, "%f", &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nKey].aKey[nCntPartsRot].fRotX);
												fscanf(pFile, "%f", &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nKey].aKey[nCntPartsRot].fRotY);
												fscanf(pFile, "%f", &g_Player.aMotionInfo[nCntMotion].aKeyInfo[nKey].aKey[nCntPartsRot].fRotZ);

												nCntPartsRot++;

											}
											else if (strcmp(aStr, "END_KEY") == 0)
											{
												break;
											}
										}
									}
									else if (strcmp(aStr, "END_KEYSET") == 0)
									{
										nKey++;
										nCntPartsPos = 0;
										nCntPartsRot = 0;
										break;
									}
								}
							}

							else if (strcmp(aStr, "END_MOTIONSET") == 0)
							{
								nKey = 0;
								nCntMotion++;
								break;
							}
						}
					}

					else if (strcmp(aStr, "END_MODELSET") == 0)
					{
						break;
					}
				}
			}

			if (strcmp(aStr, "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	else
	{
		return;
	}
	fclose(pFile);
}