//----------------------------------------
//
//モデル表示処理[blacksanta.cpp]
//Author fuma sato
//
//----------------------------------------

#include"blacksanta.h"
#include"game.h"
#include"shadow.h"
#include"input.h"
#include"file.h"
#include"particle.h"
#include"socks.h"

//グローバル変数宣言
BlackSanta g_BlackSanta;

static MOTION_INFO g_BlackSantaMotion[] =
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
void InitBlackSanta(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_BlackSanta.pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_BlackSanta.posOld = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_BlackSanta.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_BlackSanta.Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_BlackSanta.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.state = BLACKSANTASTATE_NORMAL;
	g_BlackSanta.nIdxShadow = -1;
	g_BlackSanta.pStage = NULL;

	g_BlackSanta.bLoopMotion = false;
	g_BlackSanta.motionType = MOTIONTYPE_NEUTRAL;
	g_BlackSanta.nCounterMotion = 0;
	g_BlackSanta.nKey = -1;
	g_BlackSanta.nNumKey = 0;
	g_BlackSanta.nNumMotion = NUM_MOTION_BLACKSANTA;
	g_BlackSanta.bUse = false;

	LoadModel();

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_BODY_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[0].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[0].dwNumMat,
		&g_BlackSanta.aModel[0].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_HEAD_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[1].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[1].dwNumMat,
		&g_BlackSanta.aModel[1].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_RIGHTARM_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[2].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[2].dwNumMat,
		&g_BlackSanta.aModel[2].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_RIGHTHAND_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[3].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[3].dwNumMat,
		&g_BlackSanta.aModel[3].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_LEFTARM_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[4].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[4].dwNumMat,
		&g_BlackSanta.aModel[4].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_LEFTHAND_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[5].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[5].dwNumMat,
		&g_BlackSanta.aModel[5].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_RIGHTLEG_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[6].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[6].dwNumMat,
		&g_BlackSanta.aModel[6].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_RIGHTFOOT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[7].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[7].dwNumMat,
		&g_BlackSanta.aModel[7].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_LEFTLEG_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[8].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[8].dwNumMat,
		&g_BlackSanta.aModel[8].pMesh
	);

	//Xファイル読み込み
	D3DXLoadMeshFromX
	(
		BLACKSANTA_LEFTFOOT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BlackSanta.aModel[9].pBuffMat,
		NULL,
		&g_BlackSanta.aModel[9].dwNumMat,
		&g_BlackSanta.aModel[9].pMesh
	);

	g_BlackSanta.nNumModel = NUM_MODEL_BLACKSANTA;

	int nCntModel;
	for (nCntModel = 0; nCntModel < g_BlackSanta.nNumModel; nCntModel++)
	{

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_BlackSanta.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_BlackSanta.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャがある
				//テクスチャの読み込み
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_BlackSanta.aModel[nCntModel].apTexture[nCntMat]
				);
			}
		}

		//頂点数
		g_BlackSanta.aModel[nCntModel].nNumVtx = g_BlackSanta.aModel[nCntModel].pMesh->GetNumVertices();
		//頂点サイズ
		g_BlackSanta.aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_BlackSanta.aModel[nCntModel].pMesh->GetFVF());
		//頂点バッファの取得
		g_BlackSanta.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_BlackSanta.aModel[nCntModel].pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < g_BlackSanta.aModel[nCntModel].nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_BlackSanta.aModel[nCntModel].pVtxBuff;

			if (vtx.x > g_BlackSanta.aModel[nCntModel].vtxMax.x)
			{
				g_BlackSanta.aModel[nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.x < g_BlackSanta.aModel[nCntModel].vtxMin.x)
			{
				g_BlackSanta.aModel[nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y > g_BlackSanta.aModel[nCntModel].vtxMax.y)
			{
				g_BlackSanta.aModel[nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.y < g_BlackSanta.aModel[nCntModel].vtxMin.y)
			{
				g_BlackSanta.aModel[nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z > g_BlackSanta.aModel[nCntModel].vtxMax.z)
			{
				g_BlackSanta.aModel[nCntModel].vtxMax.z = vtx.z;
			}
			if (vtx.z < g_BlackSanta.aModel[nCntModel].vtxMin.z)
			{
				g_BlackSanta.aModel[nCntModel].vtxMin.z = vtx.z;
			}

			g_BlackSanta.aModel[nCntModel].pVtxBuff += g_BlackSanta.aModel[nCntModel].sizeFVF;
		}

		g_BlackSanta.aModel[nCntModel].vtxMinDef = g_BlackSanta.aModel[nCntModel].vtxMin;
		g_BlackSanta.aModel[nCntModel].vtxMaxDef = g_BlackSanta.aModel[nCntModel].vtxMax;
	}

	g_BlackSanta.aModel[0].nIdxModelParent = -1;
	g_BlackSanta.aModel[0].pos = D3DXVECTOR3(0.0f, 25.5f, 0.0f);
	g_BlackSanta.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[0].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.aModel[1].nIdxModelParent = 0;
	g_BlackSanta.aModel[1].pos = D3DXVECTOR3(0.0f, 20.0f, -3.0f);
	g_BlackSanta.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[1].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.aModel[2].nIdxModelParent = 0;
	g_BlackSanta.aModel[2].pos = D3DXVECTOR3(-10.0f, 15.0f, 0.0f);
	g_BlackSanta.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[2].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.aModel[3].nIdxModelParent = 2;
	g_BlackSanta.aModel[3].pos = D3DXVECTOR3(-20.0f, -1.0f, -3.0f);
	g_BlackSanta.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[3].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.aModel[4].nIdxModelParent = 0;
	g_BlackSanta.aModel[4].pos = D3DXVECTOR3(10.0f, 15.0f, 0.0f);
	g_BlackSanta.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[4].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.aModel[5].nIdxModelParent = 4;
	g_BlackSanta.aModel[5].pos = D3DXVECTOR3(20.5f, -2.0f, -1.0f);
	g_BlackSanta.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[5].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.aModel[6].nIdxModelParent = 0;
	g_BlackSanta.aModel[6].pos = D3DXVECTOR3(-4.0f, 1.0f, 0.0f);
	g_BlackSanta.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[6].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.aModel[7].nIdxModelParent = 6;
	g_BlackSanta.aModel[7].pos = D3DXVECTOR3(0.0f, -20.0f, 0.0f);
	g_BlackSanta.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[7].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.aModel[8].nIdxModelParent = 0;
	g_BlackSanta.aModel[8].pos = D3DXVECTOR3(4.0f, 1.0f, 0.0f);
	g_BlackSanta.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[8].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_BlackSanta.aModel[9].nIdxModelParent = 8;
	g_BlackSanta.aModel[9].pos = D3DXVECTOR3(0.0f, -20.0f, 0.0f);
	g_BlackSanta.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BlackSanta.aModel[9].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	for (int nCnt = 0; nCnt < MAX_MODEL_BLACKSANTA; nCnt++)
	{
		g_BlackSanta.aModel[nCnt].posDef = g_BlackSanta.aModel[nCnt].pos;
	}

	g_BlackSanta.nIdxShadow = SetShadow(g_BlackSanta.pos, g_BlackSanta.rot);
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitBlackSanta(void)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_MODEL_BLACKSANTA; nCntModel++)
	{
		for (unsigned int i = 0; i < g_BlackSanta.aModel[nCntModel].dwNumMat; i++)
		{
			if (g_BlackSanta.aModel[nCntModel].apTexture[i] != NULL)
			{
				g_BlackSanta.aModel[nCntModel].apTexture[i]->Release();
				g_BlackSanta.aModel[nCntModel].apTexture[i] = NULL;
			}
		}
		//メッシュの破棄
		if (g_BlackSanta.aModel[nCntModel].pMesh != NULL)
		{
			g_BlackSanta.aModel[nCntModel].pMesh->Release();
			g_BlackSanta.aModel[nCntModel].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_BlackSanta.aModel[nCntModel].pBuffMat != NULL)
		{
			g_BlackSanta.aModel[nCntModel].pBuffMat->Release();
			g_BlackSanta.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateBlackSanta(void)
{
	if (g_BlackSanta.bUse)
	{
		//移動処理

		Socks* pSocks = GetSocks();
		float Oldrot = atan2f(g_BlackSanta.move.x, g_BlackSanta.move.z);//今の方向
		float Xlong = pSocks->pos.x - g_BlackSanta.pos.x;
		float Zlong = pSocks->pos.z - g_BlackSanta.pos.z;
		float Destrot = atan2f(Xlong, Zlong);//敵の方向

		float Diffrot = Destrot - Oldrot;//差の角度
		if (Diffrot > D3DX_PI)
		{//修正
			Diffrot -= D3DX_PI * 2;
		}
		else if (Diffrot < -D3DX_PI)
		{//修正
			Diffrot += D3DX_PI * 2;
		}

		Oldrot += Diffrot * 1.0f;//角度を補正

		if (Oldrot > D3DX_PI)
		{//修正
			Oldrot -= D3DX_PI * 2;
		}
		else if (Oldrot < -D3DX_PI)
		{//修正
			Oldrot += D3DX_PI * 2;
		}

		g_BlackSanta.Destrot.y = Oldrot - D3DX_PI;
		if (g_BlackSanta.motionType != MOTIONTYPE_JUMP && g_BlackSanta.motionType != MOTIONTYPE_LANDING && g_BlackSanta.motionType != MOTIONTYPE_ACTION)
		{
			g_BlackSanta.motionType = MOTIONTYPE_MOVE;
		}

		g_BlackSanta.move.y += GRAVITY;

		g_BlackSanta.posOld = g_BlackSanta.pos;

		//位置の更新
		g_BlackSanta.pos.x += g_BlackSanta.move.x;
		g_BlackSanta.pos.y += g_BlackSanta.move.y;
		g_BlackSanta.pos.z += g_BlackSanta.move.z;

		//移動量の更新(減衰)
		g_BlackSanta.move.x += (BLACKSANTA_SPEED_DEF - g_BlackSanta.move.x) * BLACKSANTA_INA;
		g_BlackSanta.move.z += (BLACKSANTA_SPEED_DEF - g_BlackSanta.move.z) * BLACKSANTA_INA;

		g_BlackSanta.pStage = NULL;

		CollisionStage(&g_BlackSanta.pStage);

		if (g_BlackSanta.pStage != NULL)
		{
			g_BlackSanta.pos += g_BlackSanta.pStage->move;
		}

		if (g_BlackSanta.pos.x < -GAME_WALL)
		{
			g_BlackSanta.pos.x = -GAME_WALL;
		}
		if (g_BlackSanta.pos.x > GAME_WALL)
		{
			g_BlackSanta.pos.x = GAME_WALL;
		}
		if (g_BlackSanta.pos.z < -GAME_WALL)
		{
			g_BlackSanta.pos.z = -GAME_WALL;
		}
		if (g_BlackSanta.pos.z > GAME_WALL)
		{
			g_BlackSanta.pos.z = GAME_WALL;
		}

		if (sqrtf(g_BlackSanta.move.x * g_BlackSanta.move.x + g_BlackSanta.move.z * g_BlackSanta.move.z) < 1.0f && g_BlackSanta.motionType == MOTIONTYPE_MOVE)
		{
			g_BlackSanta.move.x = 0.0f;
			g_BlackSanta.move.z = 0.0f;
			g_BlackSanta.motionType = MOTIONTYPE_NEUTRAL;
		}

		//正規化
		if (g_BlackSanta.Destrot.y > D3DX_PI)
		{
			g_BlackSanta.Destrot.y -= D3DX_PI * 2.0f;
		}
		else if (g_BlackSanta.Destrot.y < -D3DX_PI)
		{
			g_BlackSanta.Destrot.y += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_BlackSanta.Destrot.y - g_BlackSanta.rot.y > D3DX_PI)
		{
			g_BlackSanta.Destrot.y = g_BlackSanta.rot.y + ((g_BlackSanta.Destrot.y - g_BlackSanta.rot.y) - D3DX_PI * 2.0f);
		}
		else if (g_BlackSanta.Destrot.y - g_BlackSanta.rot.y < -D3DX_PI)
		{
			g_BlackSanta.Destrot.y = g_BlackSanta.rot.y + ((g_BlackSanta.Destrot.y - g_BlackSanta.rot.y) + D3DX_PI * 2.0f);
		}

		g_BlackSanta.rot.y += (g_BlackSanta.Destrot.y - g_BlackSanta.rot.y) * BLACKSANTA_ROT_SPEED;

		//正規化
		if (g_BlackSanta.rot.y > D3DX_PI)
		{
			g_BlackSanta.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_BlackSanta.rot.y < -D3DX_PI)
		{
			g_BlackSanta.rot.y += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_BlackSanta.Destrot.x > D3DX_PI)
		{
			g_BlackSanta.Destrot.x -= D3DX_PI * 2.0f;
		}
		else if (g_BlackSanta.Destrot.x < -D3DX_PI)
		{
			g_BlackSanta.Destrot.x += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_BlackSanta.Destrot.x - g_BlackSanta.rot.x > D3DX_PI)
		{
			g_BlackSanta.Destrot.x = g_BlackSanta.rot.x + ((g_BlackSanta.Destrot.x - g_BlackSanta.rot.x) - D3DX_PI * 2.0f);
		}
		else if (g_BlackSanta.Destrot.x - g_BlackSanta.rot.x < -D3DX_PI)
		{
			g_BlackSanta.Destrot.x = g_BlackSanta.rot.x + ((g_BlackSanta.Destrot.x - g_BlackSanta.rot.x) + D3DX_PI * 2.0f);
		}

		g_BlackSanta.rot.x += (g_BlackSanta.Destrot.x - g_BlackSanta.rot.x) * BLACKSANTA_ROT_SPEED;

		//正規化
		if (g_BlackSanta.rot.x > D3DX_PI)
		{
			g_BlackSanta.rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_BlackSanta.rot.x < -D3DX_PI)
		{
			g_BlackSanta.rot.x += D3DX_PI * 2.0f;
		}

		//スケール制限
		g_BlackSanta.scale.x = max(BLACKSANTA_SCALE_MIN, min(BLACKSANTA_SCALE_MAX, g_BlackSanta.scale.x));
		g_BlackSanta.scale.y = max(BLACKSANTA_SCALE_MIN, min(BLACKSANTA_SCALE_MAX, g_BlackSanta.scale.y));
		g_BlackSanta.scale.z = max(BLACKSANTA_SCALE_MIN, min(BLACKSANTA_SCALE_MAX, g_BlackSanta.scale.z));

		int nCntModel;
		//パーツ分回す
		for (nCntModel = 0; nCntModel < g_BlackSanta.nNumModel; nCntModel++)
		{
			g_BlackSanta.aModel[nCntModel].vtxMax.x = g_BlackSanta.aModel[nCntModel].vtxMaxDef.x * g_BlackSanta.scale.x;
			g_BlackSanta.aModel[nCntModel].vtxMax.y = g_BlackSanta.aModel[nCntModel].vtxMaxDef.y * g_BlackSanta.scale.y;
			g_BlackSanta.aModel[nCntModel].vtxMax.z = g_BlackSanta.aModel[nCntModel].vtxMaxDef.z * g_BlackSanta.scale.z;
			g_BlackSanta.aModel[nCntModel].vtxMin.x = g_BlackSanta.aModel[nCntModel].vtxMinDef.x * g_BlackSanta.scale.x;
			g_BlackSanta.aModel[nCntModel].vtxMin.y = g_BlackSanta.aModel[nCntModel].vtxMinDef.y * g_BlackSanta.scale.y;
			g_BlackSanta.aModel[nCntModel].vtxMin.z = g_BlackSanta.aModel[nCntModel].vtxMinDef.z * g_BlackSanta.scale.z;
		}

		//UpdateBlackSantaMotion();

		switch (g_BlackSanta.state)
		{
		case BLACKSANTASTATE_APPEAR:
			g_BlackSanta.bUse = false;
			break;
		case BLACKSANTASTATE_NORMAL:
			SetPositionShadow(g_BlackSanta.nIdxShadow, g_BlackSanta.pos, g_BlackSanta.scale, 200.0f);
			break;
		case BLACKSANTASTATE_DIE:
			g_BlackSanta.Destrot.x = D3DX_PI * 0.5f;
			static int nCnt = 0;
			nCnt++;
			if (nCnt >= 20)
			{
				NullShadow(g_BlackSanta.nIdxShadow);
				SetParticle(g_BlackSanta.pos, g_BlackSanta.scale,PARTICLE_TYPE_NONE);
				g_BlackSanta.state = BLACKSANTASTATE_APPEAR;
			}
			break;
		}
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawBlackSanta(void)
{
	if (g_BlackSanta.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
		D3DMATERIAL9 matDef;//現在のマテリアル保存用
		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ


		//デバイスの取得
		pDevice = GetDevice();

		//マトリックス初期化
		D3DXMatrixIdentity(&g_BlackSanta.mtxWorld);

		//大きさの反映
		D3DXMatrixScaling(&mtxScale, g_BlackSanta.scale.x, g_BlackSanta.scale.y, g_BlackSanta.scale.z);
		D3DXMatrixMultiply(&g_BlackSanta.mtxWorld, &g_BlackSanta.mtxWorld, &mtxScale);

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_BlackSanta.rot.y, g_BlackSanta.rot.x, g_BlackSanta.rot.z);
		D3DXMatrixMultiply(&g_BlackSanta.mtxWorld, &g_BlackSanta.mtxWorld, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, g_BlackSanta.pos.x, g_BlackSanta.pos.y, g_BlackSanta.pos.z);
		D3DXMatrixMultiply(&g_BlackSanta.mtxWorld, &g_BlackSanta.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_BlackSanta.mtxWorld);

		int nCntModel;
		//パーツ分回す
		for (nCntModel = 0; nCntModel < g_BlackSanta.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//計算マトリックス
			D3DXMATRIX mtxParent;
			//マトリックス初期化
			D3DXMatrixIdentity(&g_BlackSanta.aModel[nCntModel].mtxWorld);

			//大きさの反映
			D3DXMatrixScaling(&mtxScaleModel, g_BlackSanta.aModel[nCntModel].scale.x, g_BlackSanta.aModel[nCntModel].scale.y, g_BlackSanta.aModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_BlackSanta.aModel[nCntModel].mtxWorld, &g_BlackSanta.aModel[nCntModel].mtxWorld, &mtxScaleModel);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_BlackSanta.aModel[nCntModel].rot.y, g_BlackSanta.aModel[nCntModel].rot.x, g_BlackSanta.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_BlackSanta.aModel[nCntModel].mtxWorld, &g_BlackSanta.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置の反映
			D3DXMatrixTranslation(&mtxTransModel, g_BlackSanta.aModel[nCntModel].pos.x, g_BlackSanta.aModel[nCntModel].pos.y, g_BlackSanta.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_BlackSanta.aModel[nCntModel].mtxWorld, &g_BlackSanta.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスの設定
			if (g_BlackSanta.aModel[nCntModel].nIdxModelParent != -1)
			{//親モデルがある
				mtxParent = g_BlackSanta.aModel[g_BlackSanta.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//親モデルがない
				mtxParent = g_BlackSanta.mtxWorld;
			}

			D3DXMatrixMultiply(&g_BlackSanta.aModel[nCntModel].mtxWorld, &g_BlackSanta.aModel[nCntModel].mtxWorld, &mtxParent);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_BlackSanta.aModel[nCntModel].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_BlackSanta.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_BlackSanta.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャ
				pDevice->SetTexture(0, g_BlackSanta.aModel[nCntModel].apTexture[nCntMat]);

				//モデル描画
				g_BlackSanta.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------
//出現
//-----------------------------
void SetBlackSanta(D3DXVECTOR3 pos)
{
	if (!g_BlackSanta.bUse)
	{
		g_BlackSanta.pos = pos;

		g_BlackSanta.posOld = pos;
		g_BlackSanta.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_BlackSanta.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_BlackSanta.Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_BlackSanta.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_BlackSanta.state = BLACKSANTASTATE_NORMAL;
		g_BlackSanta.nIdxShadow = SetShadow(g_BlackSanta.pos, g_BlackSanta.rot);
		g_BlackSanta.pStage = NULL;

		g_BlackSanta.bLoopMotion = false;
		g_BlackSanta.motionType = MOTIONTYPE_NEUTRAL;
		g_BlackSanta.nCounterMotion = 0;
		g_BlackSanta.nKey = -1;
		g_BlackSanta.nNumKey = 0;
		g_BlackSanta.nNumMotion = NUM_MOTION_BLACKSANTA;

		g_BlackSanta.bUse = true;
	}
}

//-----------------------------
//破棄
//-----------------------------
void EndBlackSanta(void)
{
	if (g_BlackSanta.bUse)
	{
		g_BlackSanta.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_BlackSanta.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_BlackSanta.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_BlackSanta.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_BlackSanta.Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_BlackSanta.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_BlackSanta.state = BLACKSANTASTATE_NORMAL;
		NullShadow(g_BlackSanta.nIdxShadow);
		g_BlackSanta.nIdxShadow = -1;
		g_BlackSanta.pStage = NULL;

		g_BlackSanta.bLoopMotion = false;
		g_BlackSanta.motionType = MOTIONTYPE_NEUTRAL;
		g_BlackSanta.nCounterMotion = 0;
		g_BlackSanta.nKey = -1;
		g_BlackSanta.nNumKey = 0;
		g_BlackSanta.nNumMotion = NUM_MOTION_BLACKSANTA;

		g_BlackSanta.bUse = false;
	}
}

//------------------------------
//位置取得
//------------------------------
BlackSanta* GetBlackSanta(void)
{
	return &g_BlackSanta;
}

//------------------------------
//モーション
//------------------------------
void UpdateBlackSantaMotion(void)
{
	static MOTIONTYPE OldMotion = MOTIONTYPE_NEUTRAL;
	static int BlendCnt = 0;
	if (OldMotion != g_BlackSanta.motionType)
	{
		g_BlackSanta.aMotionInfo[OldMotion] = g_BlackSantaMotion[OldMotion];
		g_BlackSanta.aMotionInfo[g_BlackSanta.motionType] = g_BlackSantaMotion[g_BlackSanta.motionType];

		for (int nCntModel = 0; nCntModel < g_BlackSanta.nNumModel; nCntModel++)
		{
			D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_BlackSanta.aMotionInfo[OldMotion].aKeyInfo[g_BlackSanta.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosX, g_BlackSanta.aMotionInfo[OldMotion].aKeyInfo[g_BlackSanta.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosY, g_BlackSanta.aMotionInfo[OldMotion].aKeyInfo[g_BlackSanta.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 Destpos = D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[0].aKey[nCntModel].fPosX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[0].aKey[nCntModel].fPosY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[0].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 posDif = Destpos - Oldpos;

			D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_BlackSanta.aMotionInfo[OldMotion].aKeyInfo[g_BlackSanta.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotX, g_BlackSanta.aMotionInfo[OldMotion].aKeyInfo[g_BlackSanta.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotY, g_BlackSanta.aMotionInfo[OldMotion].aKeyInfo[g_BlackSanta.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotZ);
			D3DXVECTOR3 Destrot = D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[0].aKey[nCntModel].fRotX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[0].aKey[nCntModel].fRotY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[0].aKey[nCntModel].fRotZ);

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

			g_BlackSanta.aModel[nCntModel].pos = g_BlackSanta.aModel[nCntModel].posDef + Oldpos + posDif * (BlendCnt / BLACKSANTA_BLEND_FRAME);
			g_BlackSanta.aModel[nCntModel].rot = Oldrot + rotDif * (BlendCnt / BLACKSANTA_BLEND_FRAME);

			//正規化
			if (g_BlackSanta.aModel[nCntModel].rot.x > D3DX_PI)
			{
				g_BlackSanta.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_BlackSanta.aModel[nCntModel].rot.x < -D3DX_PI)
			{
				g_BlackSanta.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			//正規化
			if (g_BlackSanta.aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_BlackSanta.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_BlackSanta.aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_BlackSanta.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			//正規化
			if (g_BlackSanta.aModel[nCntModel].rot.z > D3DX_PI)
			{
				g_BlackSanta.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
			else if (g_BlackSanta.aModel[nCntModel].rot.z < -D3DX_PI)
			{
				g_BlackSanta.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
		}

		if (BlendCnt == (int)BLACKSANTA_BLEND_FRAME)
		{
			BlendCnt = 0;
			OldMotion = g_BlackSanta.motionType;
			return;
		}
		BlendCnt++;
		return;
	}
	g_BlackSanta.aMotionInfo[g_BlackSanta.motionType] = g_BlackSantaMotion[g_BlackSanta.motionType];
	g_BlackSanta.nNumKey = g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].nNumKey;
	g_BlackSanta.bLoopMotion = g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].bLoop;
	static int nDestKey = g_BlackSanta.nKey + 1;

	if (g_BlackSanta.nCounterMotion >= g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].nFrame)
	{
		g_BlackSanta.nCounterMotion = 0;
	}

	if (g_BlackSanta.nCounterMotion == 0)
	{
		if (nDestKey >= g_BlackSanta.nNumKey - 1)
		{
			if (g_BlackSanta.bLoopMotion)
			{
				g_BlackSanta.nKey++;
				nDestKey = 0;

				for (int nCntModel = 0; nCntModel < g_BlackSanta.nNumModel; nCntModel++)
				{
					g_BlackSanta.aModel[nCntModel].pos = g_BlackSanta.aModel[nCntModel].posDef + D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fPosX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fPosY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fPosZ);
					g_BlackSanta.aModel[nCntModel].rot = D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fRotX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fRotY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fRotZ);
				}
			}
			else
			{
				g_BlackSanta.nKey = -1;
				nDestKey = g_BlackSanta.nKey + 1;
				g_BlackSanta.motionType = MOTIONTYPE_NEUTRAL;
				return;
			}
		}
		else
		{
			g_BlackSanta.nKey++;
			if (g_BlackSanta.nKey > g_BlackSanta.nNumKey - 1)
			{
				g_BlackSanta.nKey = 0;
			}
			nDestKey = g_BlackSanta.nKey + 1;

			for (int nCntModel = 0; nCntModel < g_BlackSanta.nNumModel; nCntModel++)
			{
				g_BlackSanta.aModel[nCntModel].pos = g_BlackSanta.aModel[nCntModel].posDef + D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fPosX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fPosY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fPosZ);
				g_BlackSanta.aModel[nCntModel].rot = D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fRotX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fRotY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fRotZ);
			}
		}
	}

	for (int nCntModel = 0; nCntModel < g_BlackSanta.nNumModel; nCntModel++)
	{
		D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fPosX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fPosY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 Destpos = D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 posDif = Destpos - Oldpos;

		D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fRotX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fRotY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].aKey[nCntModel].fRotZ);
		D3DXVECTOR3 Destrot = D3DXVECTOR3(g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotX, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotY, g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotZ);

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

		g_BlackSanta.aModel[nCntModel].pos = g_BlackSanta.aModel[nCntModel].posDef + Oldpos + posDif * (g_BlackSanta.nCounterMotion / (float)g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].nFrame);
		g_BlackSanta.aModel[nCntModel].rot = Oldrot + rotDif * (g_BlackSanta.nCounterMotion / (float)g_BlackSanta.aMotionInfo[g_BlackSanta.motionType].aKeyInfo[g_BlackSanta.nKey].nFrame);

		//正規化
		if (g_BlackSanta.aModel[nCntModel].rot.x > D3DX_PI)
		{
			g_BlackSanta.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_BlackSanta.aModel[nCntModel].rot.x < -D3DX_PI)
		{
			g_BlackSanta.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		//正規化
		if (g_BlackSanta.aModel[nCntModel].rot.y > D3DX_PI)
		{
			g_BlackSanta.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_BlackSanta.aModel[nCntModel].rot.y < -D3DX_PI)
		{
			g_BlackSanta.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}
		//正規化
		if (g_BlackSanta.aModel[nCntModel].rot.z > D3DX_PI)
		{
			g_BlackSanta.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		else if (g_BlackSanta.aModel[nCntModel].rot.z < -D3DX_PI)
		{
			g_BlackSanta.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
	g_BlackSanta.nCounterMotion++;
}

//------------------------------------------------
//衝突
//------------------------------------------------
void CollisionBlackSanta(D3DXVECTOR3 pos, float Length)
{
	float Space = sqrtf((pos.x - g_BlackSanta.pos.x) * (pos.x - g_BlackSanta.pos.x) + (pos.y - g_BlackSanta.pos.y) * (pos.y - g_BlackSanta.pos.y) + (pos.z - g_BlackSanta.pos.z) * (pos.z - g_BlackSanta.pos.z));
	if (Space < BLACKSANTA_SIZE * 0.5f + Length * 0.5f)
	{
		Space = (BLACKSANTA_SIZE * 0.5f + Length * 0.5f) - Space;
		D3DXVECTOR3 Hitvec = g_BlackSanta.pos - pos;
		D3DXVec3Normalize(&Hitvec, &Hitvec);
		g_BlackSanta.move += Hitvec * Space;
	}
}