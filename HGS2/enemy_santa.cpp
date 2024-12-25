//----------------------------------------
//
//モデル表示処理[player.cpp]
//Author fuma sato
//
//----------------------------------------

#include"enemy_santa.h"
#include"game.h"
#include"shadow.h"
#include"camera.h"
#include"input.h"
#include"bullet.h"
#include"file.h"
#include"particle.h"
#include"life.h"
#include"snowball.h"

//グローバル変数宣言
Enemy g_Enemy;

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
//ポリゴンの初期化処理
//----------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Enemy.pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_Enemy.posOld = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_Enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Enemy.Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Enemy.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.bJump = false;
	g_Enemy.nLife = SANTA_LIFE;
	g_Enemy.state = SANTASTATE_NORMAL;
	g_Enemy.nIdxShadow = -1;
	g_Enemy.nIdxLife = -1;
	g_Enemy.pStage = NULL;

	g_Enemy.bLoopMotion = false;
	g_Enemy.motionType = MOTIONTYPE_NEUTRAL;
	g_Enemy.nCounterMotion = 0;
	g_Enemy.nKey = -1;
	g_Enemy.nNumKey = 0;
	g_Enemy.nNumMotion = NUM_MOTION;
	g_Enemy.bUse = true;

	LoadModel();

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_BODY_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[0].pBuffMat,
		NULL,
		&g_Enemy.aModel[0].dwNumMat,
		&g_Enemy.aModel[0].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_HEAD_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[1].pBuffMat,
		NULL,
		&g_Enemy.aModel[1].dwNumMat,
		&g_Enemy.aModel[1].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_RIGHTARM_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[2].pBuffMat,
		NULL,
		&g_Enemy.aModel[2].dwNumMat,
		&g_Enemy.aModel[2].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_RIGHTHAND_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[3].pBuffMat,
		NULL,
		&g_Enemy.aModel[3].dwNumMat,
		&g_Enemy.aModel[3].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_LEFTARM_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[4].pBuffMat,
		NULL,
		&g_Enemy.aModel[4].dwNumMat,
		&g_Enemy.aModel[4].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_LEFTHAND_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[5].pBuffMat,
		NULL,
		&g_Enemy.aModel[5].dwNumMat,
		&g_Enemy.aModel[5].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_RIGHTLEG_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[6].pBuffMat,
		NULL,
		&g_Enemy.aModel[6].dwNumMat,
		&g_Enemy.aModel[6].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_RIGHTFOOT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[7].pBuffMat,
		NULL,
		&g_Enemy.aModel[7].dwNumMat,
		&g_Enemy.aModel[7].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_LEFTLEG_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[8].pBuffMat,
		NULL,
		&g_Enemy.aModel[8].dwNumMat,
		&g_Enemy.aModel[8].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		SANTA_LEFTFOOT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy.aModel[9].pBuffMat,
		NULL,
		&g_Enemy.aModel[9].dwNumMat,
		&g_Enemy.aModel[9].pMesh
	);

	g_Enemy.nNumModel = NUM_MODEL;

	int nCntModel;
	for (nCntModel = 0;  nCntModel < g_Enemy.nNumModel; nCntModel++)
	{

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Enemy.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Enemy.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャがある
				//テクスチャの読み込み
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Enemy.aModel[nCntModel].apTexture[nCntMat]
				);
			}
		}

		//頂点数
		g_Enemy.aModel[nCntModel].nNumVtx = g_Enemy.aModel[nCntModel].pMesh->GetNumVertices();
		//頂点サイズ
		g_Enemy.aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_Enemy.aModel[nCntModel].pMesh->GetFVF());
		//頂点バッファの取得
		g_Enemy.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Enemy.aModel[nCntModel].pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < g_Enemy.aModel[nCntModel].nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Enemy.aModel[nCntModel].pVtxBuff;

			if (vtx.x > g_Enemy.aModel[nCntModel].vtxMax.x)
			{
				g_Enemy.aModel[nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.x < g_Enemy.aModel[nCntModel].vtxMin.x)
			{
				g_Enemy.aModel[nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y > g_Enemy.aModel[nCntModel].vtxMax.y)
			{
				g_Enemy.aModel[nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.y < g_Enemy.aModel[nCntModel].vtxMin.y)
			{
				g_Enemy.aModel[nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z > g_Enemy.aModel[nCntModel].vtxMax.z)
			{
				g_Enemy.aModel[nCntModel].vtxMax.z = vtx.z;
			}
			if (vtx.z < g_Enemy.aModel[nCntModel].vtxMin.z)
			{
				g_Enemy.aModel[nCntModel].vtxMin.z = vtx.z;
			}

			g_Enemy.aModel[nCntModel].pVtxBuff += g_Enemy.aModel[nCntModel].sizeFVF;
		}

		g_Enemy.aModel[nCntModel].vtxMinDef = g_Enemy.aModel[nCntModel].vtxMin;
		g_Enemy.aModel[nCntModel].vtxMaxDef = g_Enemy.aModel[nCntModel].vtxMax;
	}

	g_Enemy.aModel[0].nIdxModelParent = -1;
	g_Enemy.aModel[0].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_Enemy.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[0].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.aModel[1].nIdxModelParent = 0;
	g_Enemy.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_Enemy.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[1].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.aModel[2].nIdxModelParent = 0;
	g_Enemy.aModel[2].pos = D3DXVECTOR3(-7.5f, 12.0f, 0.0f);
	g_Enemy.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[2].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.aModel[3].nIdxModelParent = 2;
	g_Enemy.aModel[3].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_Enemy.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[3].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.aModel[4].nIdxModelParent = 0;
	g_Enemy.aModel[4].pos = D3DXVECTOR3(7.5f, 12.0f, 0.0f);
	g_Enemy.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[4].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.aModel[5].nIdxModelParent = 4;
	g_Enemy.aModel[5].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_Enemy.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[5].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.aModel[6].nIdxModelParent = 0;
	g_Enemy.aModel[6].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
	g_Enemy.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[6].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.aModel[7].nIdxModelParent = 6;
	g_Enemy.aModel[7].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
	g_Enemy.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[7].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.aModel[8].nIdxModelParent = 0;
	g_Enemy.aModel[8].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
	g_Enemy.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[8].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Enemy.aModel[9].nIdxModelParent = 8;
	g_Enemy.aModel[9].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
	g_Enemy.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.aModel[9].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		g_Enemy.aModel[nCnt].posDef = g_Enemy.aModel[nCnt].pos;
	}

	g_Enemy.nIdxShadow = SetShadow(g_Enemy.pos, g_Enemy.rot);
	g_Enemy.nIdxLife = LinkLife();
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitEnemy(void)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		for (unsigned int i = 0; i < g_Enemy.aModel[nCntModel].dwNumMat; i++)
		{
			if (g_Enemy.aModel[nCntModel].apTexture[i] != NULL)
			{
				g_Enemy.aModel[nCntModel].apTexture[i]->Release();
				g_Enemy.aModel[nCntModel].apTexture[i] = NULL;
			}
		}
		//メッシュの破棄
		if (g_Enemy.aModel[nCntModel].pMesh != NULL)
		{
			g_Enemy.aModel[nCntModel].pMesh->Release();
			g_Enemy.aModel[nCntModel].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_Enemy.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Enemy.aModel[nCntModel].pBuffMat->Release();
			g_Enemy.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateEnemy(void)
{
	if (g_Enemy.bUse)
	{
		Camera* pCamera = GetCamera();
		float* pStick;

		//移動処理

		//X
		if (IsXInputControllerConnected(CONTROLLER_1))
		{
			//左スティック処理
			pStick = GetJoyStick(STICK_LEFT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f + -atan2f(*(pStick + 1), *pStick);
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		//d
		else if (IsDirectInputControllerConnected(CONTROLLER_1))
		{

			//左スティック処理
			pStick = GetdJoyStick(STICK_LEFT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f + atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f + atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f + atan2f(*(pStick + 1), *pStick);
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
		}

		if (GetKeyboradPress(DIK_A) == true || GetJoykeyPress(JOYKEY_LEFT, CONTROLLER_1) == true)//Aキー
		{
			if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//Wキー
			{//左上
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * 0.75f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//Sキー
			{//左下
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * 0.25f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else
			{//左
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * 0.5f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		else if (GetKeyboradPress(DIK_D) == true || GetJoykeyPress(JOYKEY_RIGHT, CONTROLLER_1) == true)//Dキー
		{
			if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//Wキー
			{//右上
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * -0.75f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//Sキー
			{//右下
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * -0.25f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else
			{//右
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		else if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//Wキー
		{//上
			g_Enemy.move.x += sinf(pCamera->rot.y) * SPEED;
			g_Enemy.move.z += cosf(pCamera->rot.y) * SPEED;
			g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI;
			if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
			{
				g_Enemy.motionType = MOTIONTYPE_MOVE;
			}
		}
		else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//Sキー
		{//下
			g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI) * SPEED;
			g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI) * SPEED;
			g_Enemy.Destrot.y = pCamera->rot.y;
			if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
			{
				g_Enemy.motionType = MOTIONTYPE_MOVE;
			}
		}

		if (GetKeyboradTrigger(DIK_SPACE) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_1) == true)//Sキー
		{//上
			if (!g_Enemy.bJump)
			{
				g_Enemy.move.y += JUMP;
				g_Enemy.bJump = true;
				g_Enemy.motionType = MOTIONTYPE_JUMP;
			}
		}

		if (GetKeyboradTrigger(DIK_RETURN) == true || GetMouseTrigger(MOUSE_LEFT) == true || GetJoykeyTrigger(JOYKEY_X, CONTROLLER_1) == true)
		{
			g_Enemy.motionType = MOTIONTYPE_ACTION;
		}

		if (!IsXInputControllerConnected(CONTROLLER_1) && IsDirectInputControllerConnected(CONTROLLER_1))
		{
			if (GetdJoyPov(POV_UP, 0, CONTROLLER_1) == true)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_RIGHTUP, 0, CONTROLLER_1) == true)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * -0.75f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_RIGHT, 0, CONTROLLER_1) == true)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_RIGHTDOWN, 0, CONTROLLER_1) == true)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * -0.25f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_DOWN, 0, CONTROLLER_1) == true)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_LEFTDOWN, 0, CONTROLLER_1) == true)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * 0.25f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_LEFT, 0, CONTROLLER_1) == true)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * 0.5f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_LEFTUP, 0, CONTROLLER_1) == true)
			{
				g_Enemy.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Enemy.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Enemy.Destrot.y = pCamera->rot.y + D3DX_PI * 0.75f;
				if (g_Enemy.motionType != MOTIONTYPE_JUMP && g_Enemy.motionType != MOTIONTYPE_LANDING && g_Enemy.motionType != MOTIONTYPE_ACTION)
				{
					g_Enemy.motionType = MOTIONTYPE_MOVE;
				}
			}
		}

		if (!strcmp(ControllerName(CONTROLLER_1), ELE_CON))
		{
			if (GetdJoykeyPress(ELEKEY_A, CONTROLLER_1) == true)
			{//上
				if (!g_Enemy.bJump)
				{
					g_Enemy.move.y += JUMP;
					g_Enemy.bJump = true;
					g_Enemy.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(ELEKEY_X, CONTROLLER_1) == true)
			{
				g_Enemy.motionType = MOTIONTYPE_ACTION;
			}
		}
		else if (!strcmp(ControllerName(CONTROLLER_1), PS_CON))
		{
			if (GetdJoykeyPress(PSKEY_CR, CONTROLLER_1) == true)
			{//上
				if (!g_Enemy.bJump)
				{
					g_Enemy.move.y += JUMP;
					g_Enemy.bJump = true;
					g_Enemy.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(PSKEY_SQ, CONTROLLER_1) == true)
			{
				g_Enemy.motionType = MOTIONTYPE_ACTION;
			}
		}
		else if (!strcmp(ControllerName(CONTROLLER_1), NIN_CON))
		{
			if (GetdJoykeyPress(NINKEY_B, CONTROLLER_1) == true)
			{//上
				if (!g_Enemy.bJump)
				{
					g_Enemy.move.y += JUMP;
					g_Enemy.bJump = true;
					g_Enemy.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(NINKEY_Y, CONTROLLER_1) == true)
			{
				g_Enemy.motionType = MOTIONTYPE_ACTION;
			}
		}
		else if (!IsXInputControllerConnected(CONTROLLER_1) && IsDirectInputControllerConnected(CONTROLLER_1))
		{
			if (GetdJoykeyPress(DKEY_A, CONTROLLER_1) == true)
			{//上
				if (!g_Enemy.bJump)
				{
					g_Enemy.move.y += JUMP;
					g_Enemy.bJump = true;
					g_Enemy.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(DKEY_X, CONTROLLER_1) == true)
			{
				g_Enemy.motionType = MOTIONTYPE_ACTION;
			}
		}

		g_Enemy.move.y += GRAVITY;

		if (g_Enemy.bJump)
		{
			g_Enemy.move.x *= JUMP_INA;
			g_Enemy.move.z *= JUMP_INA;
		}

		g_Enemy.posOld = g_Enemy.pos;

		//if (g_Enemy.motionType == MOTIONTYPE_ACTION)
		//{
		//	g_Enemy.move.x = 0.0f;
		//	g_Enemy.move.z = 0.0f;
		//}

		//位置の更新
		g_Enemy.pos.x += g_Enemy.move.x;
		g_Enemy.pos.y += g_Enemy.move.y;
		g_Enemy.pos.z += g_Enemy.move.z;

		//移動量の更新(減衰)
		g_Enemy.move.x += (SPEED_DEF - g_Enemy.move.x) * SANTA_INA;
		g_Enemy.move.z += (SPEED_DEF - g_Enemy.move.z) * SANTA_INA;

		g_Enemy.pStage = NULL;

		CollisionSnowBall(g_Enemy.pos, SANTA_SIZE);

		g_Enemy.bJump = !CollisionStage(&g_Enemy.pStage);

		if (g_Enemy.pStage != NULL)
		{
			g_Enemy.pos += g_Enemy.pStage->move;
		}

		if (g_Enemy.pos.x < -GAME_WALL)
		{
			g_Enemy.pos.x = -GAME_WALL;
		}
		if (g_Enemy.pos.x > GAME_WALL)
		{
			g_Enemy.pos.x = GAME_WALL;
		}
		if (g_Enemy.pos.z < -GAME_WALL)
		{
			g_Enemy.pos.z = -GAME_WALL;
		}
		if (g_Enemy.pos.z > GAME_WALL)
		{
			g_Enemy.pos.z = GAME_WALL;
		}

		if (sqrtf(g_Enemy.move.x * g_Enemy.move.x + g_Enemy.move.z * g_Enemy.move.z) < 0.1f && g_Enemy.motionType == MOTIONTYPE_MOVE)
		{
			g_Enemy.move.x = 0.0f;
			g_Enemy.move.z = 0.0f;
			g_Enemy.motionType = MOTIONTYPE_NEUTRAL;
		}

		//正規化
		if (g_Enemy.Destrot.y > D3DX_PI)
		{
			g_Enemy.Destrot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Enemy.Destrot.y < -D3DX_PI)
		{
			g_Enemy.Destrot.y += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_Enemy.Destrot.y - g_Enemy.rot.y > D3DX_PI)
		{
			g_Enemy.Destrot.y = g_Enemy.rot.y + ((g_Enemy.Destrot.y - g_Enemy.rot.y) - D3DX_PI * 2.0f);
		}
		else if (g_Enemy.Destrot.y - g_Enemy.rot.y < -D3DX_PI)
		{
			g_Enemy.Destrot.y = g_Enemy.rot.y + ((g_Enemy.Destrot.y - g_Enemy.rot.y) + D3DX_PI * 2.0f);
		}

		g_Enemy.rot.y += (g_Enemy.Destrot.y - g_Enemy.rot.y) * ROT_SPEED;

		//正規化
		if (g_Enemy.rot.y > D3DX_PI)
		{
			g_Enemy.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Enemy.rot.y < -D3DX_PI)
		{
			g_Enemy.rot.y += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_Enemy.Destrot.x > D3DX_PI)
		{
			g_Enemy.Destrot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Enemy.Destrot.x < -D3DX_PI)
		{
			g_Enemy.Destrot.x += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_Enemy.Destrot.x - g_Enemy.rot.x > D3DX_PI)
		{
			g_Enemy.Destrot.x = g_Enemy.rot.x + ((g_Enemy.Destrot.x - g_Enemy.rot.x) - D3DX_PI * 2.0f);
		}
		else if (g_Enemy.Destrot.x - g_Enemy.rot.x < -D3DX_PI)
		{
			g_Enemy.Destrot.x = g_Enemy.rot.x + ((g_Enemy.Destrot.x - g_Enemy.rot.x) + D3DX_PI * 2.0f);
		}

		g_Enemy.rot.x += (g_Enemy.Destrot.x - g_Enemy.rot.x) * ROT_SPEED;

		//正規化
		if (g_Enemy.rot.x > D3DX_PI)
		{
			g_Enemy.rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Enemy.rot.x < -D3DX_PI)
		{
			g_Enemy.rot.x += D3DX_PI * 2.0f;
		}

		//スケール制限
		g_Enemy.scale.x = max(SCALE_MIN, min(SCALE_MAX, g_Enemy.scale.x));
		g_Enemy.scale.y = max(SCALE_MIN, min(SCALE_MAX, g_Enemy.scale.y));
		g_Enemy.scale.z = max(SCALE_MIN, min(SCALE_MAX, g_Enemy.scale.z));

		int nCntModel;
		//パーツ分回す
		for (nCntModel = 0; nCntModel < g_Enemy.nNumModel; nCntModel++)
		{
			g_Enemy.aModel[nCntModel].vtxMax.x = g_Enemy.aModel[nCntModel].vtxMaxDef.x * g_Enemy.scale.x;
			g_Enemy.aModel[nCntModel].vtxMax.y = g_Enemy.aModel[nCntModel].vtxMaxDef.y * g_Enemy.scale.y;
			g_Enemy.aModel[nCntModel].vtxMax.z = g_Enemy.aModel[nCntModel].vtxMaxDef.z * g_Enemy.scale.z;
			g_Enemy.aModel[nCntModel].vtxMin.x = g_Enemy.aModel[nCntModel].vtxMinDef.x * g_Enemy.scale.x;
			g_Enemy.aModel[nCntModel].vtxMin.y = g_Enemy.aModel[nCntModel].vtxMinDef.y * g_Enemy.scale.y;
			g_Enemy.aModel[nCntModel].vtxMin.z = g_Enemy.aModel[nCntModel].vtxMinDef.z * g_Enemy.scale.z;
		}

		//UpdateMotion();

		switch (g_Enemy.state)
		{
		case SANTASTATE_APPEAR:
			g_Enemy.bUse = false;
			break;
		case SANTASTATE_NORMAL:
			if (g_Enemy.nLife <= 0)
			{
				g_Enemy.state = SANTASTATE_DIE;
			}
			SetPositionShadow(g_Enemy.nIdxShadow, g_Enemy.pos, g_Enemy.scale, 200.0f);
			SetLife(g_Enemy.pos + g_Enemy.aModel[0].pos + g_Enemy.aModel[1].pos + g_Enemy.aModel[10].pos, (float)((float)g_Enemy.nLife / (float)SANTA_LIFE), g_Enemy.nIdxLife);
			break;
		case SANTASTATE_DIE:
			g_Enemy.Destrot.x = D3DX_PI * 0.5f;
			static int nCnt = 0;
			nCnt++;
			if (nCnt >= 20)
			{
				NullShadow(g_Enemy.nIdxShadow);
				NullLife(g_Enemy.nIdxLife);
				SetParticle(g_Enemy.pos, g_Enemy.scale);
				g_Enemy.state = SANTASTATE_APPEAR;
			}
			break;
		}
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawEnemy(void)
{
	if (g_Enemy.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
		D3DMATERIAL9 matDef;//現在のマテリアル保存用
		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ


		//デバイスの取得
		pDevice = GetDevice();

		//マトリックス初期化
		D3DXMatrixIdentity(&g_Enemy.mtxWorld);

		//大きさの反映
		D3DXMatrixScaling(&mtxScale, g_Enemy.scale.x, g_Enemy.scale.y, g_Enemy.scale.z);
		D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxScale);

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy.rot.y, g_Enemy.rot.x, g_Enemy.rot.z);
		D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, g_Enemy.pos.x, g_Enemy.pos.y, g_Enemy.pos.z);
		D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.mtxWorld);

		int nCntModel;
		//パーツ分回す
		for (nCntModel = 0; nCntModel < g_Enemy.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//計算マトリックス
			D3DXMATRIX mtxParent;
			//マトリックス初期化
			D3DXMatrixIdentity(&g_Enemy.aModel[nCntModel].mtxWorld);

			//大きさの反映
			D3DXMatrixScaling(&mtxScaleModel, g_Enemy.aModel[nCntModel].scale.x, g_Enemy.aModel[nCntModel].scale.y, g_Enemy.aModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxScaleModel);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy.aModel[nCntModel].rot.y, g_Enemy.aModel[nCntModel].rot.x, g_Enemy.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置の反映
			D3DXMatrixTranslation(&mtxTransModel, g_Enemy.aModel[nCntModel].pos.x, g_Enemy.aModel[nCntModel].pos.y, g_Enemy.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスの設定
			if (g_Enemy.aModel[nCntModel].nIdxModelParent != -1)
			{//親モデルがある
				mtxParent = g_Enemy.aModel[g_Enemy.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//親モデルがない
				mtxParent = g_Enemy.mtxWorld;
			}

			D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxParent);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.aModel[nCntModel].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Enemy.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャ
				pDevice->SetTexture(0, g_Enemy.aModel[nCntModel].apTexture[nCntMat]);

				//モデル描画
				g_Enemy.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//------------------------------
//位置取得
//------------------------------
Enemy* GetEnemy(void)
{
	return &g_Enemy;
}

//------------------------------
//モーション
//------------------------------
void UpdateMotionEnemy(void)
{
	static MOTIONTYPE OldMotion = MOTIONTYPE_NEUTRAL;
	static int BlendCnt = 0;
	if (OldMotion != g_Enemy.motionType)
	{
		g_Enemy.aMotionInfo[OldMotion] = g_Motion[OldMotion];
		g_Enemy.aMotionInfo[g_Enemy.motionType] = g_Motion[g_Enemy.motionType];

		for (int nCntModel = 0; nCntModel < g_Enemy.nNumModel; nCntModel++)
		{
			D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_Enemy.aMotionInfo[OldMotion].aKeyInfo[g_Enemy.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosX, g_Enemy.aMotionInfo[OldMotion].aKeyInfo[g_Enemy.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosY, g_Enemy.aMotionInfo[OldMotion].aKeyInfo[g_Enemy.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 Destpos = D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[0].aKey[nCntModel].fPosX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[0].aKey[nCntModel].fPosY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[0].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 posDif = Destpos - Oldpos;

			D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_Enemy.aMotionInfo[OldMotion].aKeyInfo[g_Enemy.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotX, g_Enemy.aMotionInfo[OldMotion].aKeyInfo[g_Enemy.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotY, g_Enemy.aMotionInfo[OldMotion].aKeyInfo[g_Enemy.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotZ);
			D3DXVECTOR3 Destrot = D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[0].aKey[nCntModel].fRotX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[0].aKey[nCntModel].fRotY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[0].aKey[nCntModel].fRotZ);

			//正規化
			if (Destrot.x - Oldrot.x > D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
			}
			else if (Destrot.x - Oldrot.x < -D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
			}
			//正規化
			if (Destrot.y - Oldrot.y > D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
			}
			else if (Destrot.y - Oldrot.y < -D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
			}
			//正規化
			if (Destrot.z - Oldrot.z > D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
			}
			else if (Destrot.z - Oldrot.z < -D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
			}

			D3DXVECTOR3 rotDif = Destrot - Oldrot;

			g_Enemy.aModel[nCntModel].pos = g_Enemy.aModel[nCntModel].posDef + Oldpos + posDif * (BlendCnt / BLEND_FRAME);
			g_Enemy.aModel[nCntModel].rot = Oldrot + rotDif * (BlendCnt / BLEND_FRAME);

			//正規化
			if (g_Enemy.aModel[nCntModel].rot.x > D3DX_PI)
			{
				g_Enemy.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_Enemy.aModel[nCntModel].rot.x < -D3DX_PI)
			{
				g_Enemy.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			//正規化
			if (g_Enemy.aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_Enemy.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Enemy.aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_Enemy.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			//正規化
			if (g_Enemy.aModel[nCntModel].rot.z > D3DX_PI)
			{
				g_Enemy.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
			else if (g_Enemy.aModel[nCntModel].rot.z < -D3DX_PI)
			{
				g_Enemy.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
		}

		if (BlendCnt == (int)BLEND_FRAME)
		{
			BlendCnt = 0;
			OldMotion = g_Enemy.motionType;
			return;
		}
		BlendCnt++;
		return;
	}
	g_Enemy.aMotionInfo[g_Enemy.motionType] = g_Motion[g_Enemy.motionType];
	g_Enemy.nNumKey = g_Enemy.aMotionInfo[g_Enemy.motionType].nNumKey;
	g_Enemy.bLoopMotion = g_Enemy.aMotionInfo[g_Enemy.motionType].bLoop;
	static int nDestKey = g_Enemy.nKey + 1;

	if (g_Enemy.nCounterMotion >= g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].nFrame)
	{
		g_Enemy.nCounterMotion = 0;
	}

	if (g_Enemy.nCounterMotion == 0)
	{
		if (nDestKey >= g_Enemy.nNumKey - 1)
		{
			if (g_Enemy.bLoopMotion)
			{
				g_Enemy.nKey++;
				nDestKey = 0;

				for (int nCntModel = 0; nCntModel < g_Enemy.nNumModel; nCntModel++)
				{
					g_Enemy.aModel[nCntModel].pos = g_Enemy.aModel[nCntModel].posDef + D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fPosX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fPosY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fPosZ);
					g_Enemy.aModel[nCntModel].rot = D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fRotX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fRotY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fRotZ);
				}
			}
			else
			{
				g_Enemy.nKey = -1;
				nDestKey = g_Enemy.nKey + 1;
				g_Enemy.motionType = MOTIONTYPE_NEUTRAL;
				return;
			}
		}
		else
		{
			g_Enemy.nKey++;
			if (g_Enemy.nKey > g_Enemy.nNumKey - 1)
			{
				g_Enemy.nKey = 0;
			}
			nDestKey = g_Enemy.nKey + 1;

			for (int nCntModel = 0; nCntModel < g_Enemy.nNumModel; nCntModel++)
			{
				g_Enemy.aModel[nCntModel].pos = g_Enemy.aModel[nCntModel].posDef + D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fPosX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fPosY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fPosZ);
				g_Enemy.aModel[nCntModel].rot = D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fRotX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fRotY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fRotZ);
			}
		}
	}
	
	for (int nCntModel = 0; nCntModel < g_Enemy.nNumModel; nCntModel++)
	{
		D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fPosX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fPosY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 Destpos = D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 posDif = Destpos - Oldpos;

		D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fRotX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fRotY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].aKey[nCntModel].fRotZ);
		D3DXVECTOR3 Destrot = D3DXVECTOR3(g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotX, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotY, g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotZ);

		//正規化
		if (Destrot.x - Oldrot.x > D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
		}
		else if (Destrot.x - Oldrot.x < -D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
		}
		//正規化
		if (Destrot.y - Oldrot.y > D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
		}
		else if (Destrot.y - Oldrot.y < -D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
		}
		//正規化
		if (Destrot.z - Oldrot.z > D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
		}
		else if (Destrot.z - Oldrot.z < -D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
		}

		D3DXVECTOR3 rotDif = Destrot - Oldrot;

		g_Enemy.aModel[nCntModel].pos = g_Enemy.aModel[nCntModel].posDef + Oldpos + posDif * (g_Enemy.nCounterMotion / (float)g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].nFrame);
		g_Enemy.aModel[nCntModel].rot = Oldrot + rotDif * (g_Enemy.nCounterMotion / (float)g_Enemy.aMotionInfo[g_Enemy.motionType].aKeyInfo[g_Enemy.nKey].nFrame);

		//正規化
		if (g_Enemy.aModel[nCntModel].rot.x > D3DX_PI)
		{
			g_Enemy.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Enemy.aModel[nCntModel].rot.x < -D3DX_PI)
		{
			g_Enemy.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		//正規化
		if (g_Enemy.aModel[nCntModel].rot.y > D3DX_PI)
		{
			g_Enemy.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Enemy.aModel[nCntModel].rot.y < -D3DX_PI)
		{
			g_Enemy.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}
		//正規化
		if (g_Enemy.aModel[nCntModel].rot.z > D3DX_PI)
		{
			g_Enemy.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		else if (g_Enemy.aModel[nCntModel].rot.z < -D3DX_PI)
		{
			g_Enemy.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
	g_Enemy.nCounterMotion++;
}

//------------------------------------------------
//衝突
//------------------------------------------------
void CollisionEnemy(D3DXVECTOR3 pos, float Length)
{
	float Space = sqrtf((pos.x - g_Enemy.pos.x) * (pos.x - g_Enemy.pos.x) + (pos.y - g_Enemy.pos.y) * (pos.y - g_Enemy.pos.y) + (pos.z - g_Enemy.pos.z) * (pos.z - g_Enemy.pos.z));
	if (Space < SANTA_SIZE * 0.5f + Length * 0.5f)
	{
		Space = (SANTA_SIZE * 0.5f + Length * 0.5f) - Space;
		D3DXVECTOR3 Hitvec = g_Enemy.pos - pos;
		D3DXVec3Normalize(&Hitvec, &Hitvec);
		g_Enemy.move += Hitvec * Space;
	}
}