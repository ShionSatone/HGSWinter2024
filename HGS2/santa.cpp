//----------------------------------------
//
//モデル表示処理[santa.cpp]
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

//グローバル変数宣言
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
//ポリゴンの初期化処理
//----------------------
void InitSanta(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
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

	//Xファイル読み込み
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

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Santa.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Santa.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャがある
				//テクスチャの読み込み
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Santa.aModel[nCntModel].apTexture[nCntMat]
				);
			}
		}

		//頂点数
		g_Santa.aModel[nCntModel].nNumVtx = g_Santa.aModel[nCntModel].pMesh->GetNumVertices();
		//頂点サイズ
		g_Santa.aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_Santa.aModel[nCntModel].pMesh->GetFVF());
		//頂点バッファの取得
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
//ポリゴン終了処理
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
		//メッシュの破棄
		if (g_Santa.aModel[nCntModel].pMesh != NULL)
		{
			g_Santa.aModel[nCntModel].pMesh->Release();
			g_Santa.aModel[nCntModel].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_Santa.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Santa.aModel[nCntModel].pBuffMat->Release();
			g_Santa.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateSanta(void)
{
	if (g_Santa.bUse)
	{
		//移動処理
		Bed* pBed;
		float Oldrot;//今の方向
		float Xlong;
		float Zlong;
		float Destrot;//ベットの方向
		if (g_Santa.bPresent)
		{
			//移動処理
			Oldrot = atan2f(g_Santa.move.x, g_Santa.move.z);//今の方向
			Xlong = g_Santa.Startpos.x - g_Santa.pos.x;
			Zlong = g_Santa.Startpos.z - g_Santa.pos.z;
			Destrot = atan2f(Xlong, Zlong);//ベットの方向

			if (sqrtf(Xlong * Xlong + Zlong * Zlong) < PRESENT_SPACE)
			{
				EndSanta();
			}
		}
		else
		{
			//移動処理
			pBed = GetBed();
			Oldrot = atan2f(g_Santa.move.x, g_Santa.move.z);//今の方向
			Xlong = pBed->pos.x - g_Santa.pos.x;
			Zlong = pBed->pos.z + pBed->vtxMax.z - g_Santa.pos.z;
			Destrot = atan2f(Xlong, Zlong);//ベットの方向

			if (sqrtf(Xlong * Xlong + Zlong * Zlong) < PRESENT_SPACE)
			{
				g_Santa.bPresent = true;
			}
			SetPresentPos(g_Santa.pos);
		}

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

		g_Santa.move.x += sinf(Oldrot) * SANTA_SPEED;
		g_Santa.move.z += cosf(Oldrot) * SANTA_SPEED;
		g_Santa.Destrot.y = Oldrot - D3DX_PI;
		if (g_Santa.motionType != MOTIONTYPE_JUMP && g_Santa.motionType != MOTIONTYPE_LANDING && g_Santa.motionType != MOTIONTYPE_ACTION)
		{
			g_Santa.motionType = MOTIONTYPE_MOVE;
		}

		g_Santa.move.y += GRAVITY;

		g_Santa.posOld = g_Santa.pos;

		//位置の更新
		g_Santa.pos.x += g_Santa.move.x;
		g_Santa.pos.y += g_Santa.move.y;
		g_Santa.pos.z += g_Santa.move.z;

		//移動量の更新(減衰)
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

		//正規化
		if (g_Santa.Destrot.y > D3DX_PI)
		{
			g_Santa.Destrot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.Destrot.y < -D3DX_PI)
		{
			g_Santa.Destrot.y += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_Santa.Destrot.y - g_Santa.rot.y > D3DX_PI)
		{
			g_Santa.Destrot.y = g_Santa.rot.y + ((g_Santa.Destrot.y - g_Santa.rot.y) - D3DX_PI * 2.0f);
		}
		else if (g_Santa.Destrot.y - g_Santa.rot.y < -D3DX_PI)
		{
			g_Santa.Destrot.y = g_Santa.rot.y + ((g_Santa.Destrot.y - g_Santa.rot.y) + D3DX_PI * 2.0f);
		}

		g_Santa.rot.y += (g_Santa.Destrot.y - g_Santa.rot.y) * SANTA_ROT_SPEED;

		//正規化
		if (g_Santa.rot.y > D3DX_PI)
		{
			g_Santa.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.rot.y < -D3DX_PI)
		{
			g_Santa.rot.y += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_Santa.Destrot.x > D3DX_PI)
		{
			g_Santa.Destrot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.Destrot.x < -D3DX_PI)
		{
			g_Santa.Destrot.x += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_Santa.Destrot.x - g_Santa.rot.x > D3DX_PI)
		{
			g_Santa.Destrot.x = g_Santa.rot.x + ((g_Santa.Destrot.x - g_Santa.rot.x) - D3DX_PI * 2.0f);
		}
		else if (g_Santa.Destrot.x - g_Santa.rot.x < -D3DX_PI)
		{
			g_Santa.Destrot.x = g_Santa.rot.x + ((g_Santa.Destrot.x - g_Santa.rot.x) + D3DX_PI * 2.0f);
		}

		g_Santa.rot.x += (g_Santa.Destrot.x - g_Santa.rot.x) * SANTA_ROT_SPEED;

		//正規化
		if (g_Santa.rot.x > D3DX_PI)
		{
			g_Santa.rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.rot.x < -D3DX_PI)
		{
			g_Santa.rot.x += D3DX_PI * 2.0f;
		}

		//スケール制限
		g_Santa.scale.x = max(SANTA_SCALE_MIN, min(SANTA_SCALE_MAX, g_Santa.scale.x));
		g_Santa.scale.y = max(SANTA_SCALE_MIN, min(SANTA_SCALE_MAX, g_Santa.scale.y));
		g_Santa.scale.z = max(SANTA_SCALE_MIN, min(SANTA_SCALE_MAX, g_Santa.scale.z));

		int nCntModel;
		//パーツ分回す
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
//ポリゴン描画処理
//-------------------
void DrawSanta(void)
{
	if (g_Santa.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
		D3DMATERIAL9 matDef;//現在のマテリアル保存用
		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ


		//デバイスの取得
		pDevice = GetDevice();

		//マトリックス初期化
		D3DXMatrixIdentity(&g_Santa.mtxWorld);

		//大きさの反映
		D3DXMatrixScaling(&mtxScale, g_Santa.scale.x, g_Santa.scale.y, g_Santa.scale.z);
		D3DXMatrixMultiply(&g_Santa.mtxWorld, &g_Santa.mtxWorld, &mtxScale);

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Santa.rot.y, g_Santa.rot.x, g_Santa.rot.z);
		D3DXMatrixMultiply(&g_Santa.mtxWorld, &g_Santa.mtxWorld, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, g_Santa.pos.x, g_Santa.pos.y, g_Santa.pos.z);
		D3DXMatrixMultiply(&g_Santa.mtxWorld, &g_Santa.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Santa.mtxWorld);

		int nCntModel;
		//パーツ分回す
		for (nCntModel = 0; nCntModel < g_Santa.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//計算マトリックス
			D3DXMATRIX mtxParent;
			//マトリックス初期化
			D3DXMatrixIdentity(&g_Santa.aModel[nCntModel].mtxWorld);

			//大きさの反映
			D3DXMatrixScaling(&mtxScaleModel, g_Santa.aModel[nCntModel].scale.x, g_Santa.aModel[nCntModel].scale.y, g_Santa.aModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_Santa.aModel[nCntModel].mtxWorld, &g_Santa.aModel[nCntModel].mtxWorld, &mtxScaleModel);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Santa.aModel[nCntModel].rot.y, g_Santa.aModel[nCntModel].rot.x, g_Santa.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Santa.aModel[nCntModel].mtxWorld, &g_Santa.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置の反映
			D3DXMatrixTranslation(&mtxTransModel, g_Santa.aModel[nCntModel].pos.x, g_Santa.aModel[nCntModel].pos.y, g_Santa.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_Santa.aModel[nCntModel].mtxWorld, &g_Santa.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスの設定
			if (g_Santa.aModel[nCntModel].nIdxModelParent != -1)
			{//親モデルがある
				mtxParent = g_Santa.aModel[g_Santa.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//親モデルがない
				mtxParent = g_Santa.mtxWorld;
			}

			D3DXMatrixMultiply(&g_Santa.aModel[nCntModel].mtxWorld, &g_Santa.aModel[nCntModel].mtxWorld, &mtxParent);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Santa.aModel[nCntModel].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Santa.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Santa.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャ
				pDevice->SetTexture(0, g_Santa.aModel[nCntModel].apTexture[nCntMat]);

				//モデル描画
				g_Santa.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------
//出現
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
//破棄
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
//位置取得
//------------------------------
Santa* GetSanta(void)
{
	return &g_Santa;
}

//------------------------------
//モーション
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

			g_Santa.aModel[nCntModel].pos = g_Santa.aModel[nCntModel].posDef + Oldpos + posDif * (BlendCnt / SANTA_BLEND_FRAME);
			g_Santa.aModel[nCntModel].rot = Oldrot + rotDif * (BlendCnt / SANTA_BLEND_FRAME);

			//正規化
			if (g_Santa.aModel[nCntModel].rot.x > D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_Santa.aModel[nCntModel].rot.x < -D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			//正規化
			if (g_Santa.aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Santa.aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_Santa.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			//正規化
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

		g_Santa.aModel[nCntModel].pos = g_Santa.aModel[nCntModel].posDef + Oldpos + posDif * (g_Santa.nCounterMotion / (float)g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].nFrame);
		g_Santa.aModel[nCntModel].rot = Oldrot + rotDif * (g_Santa.nCounterMotion / (float)g_Santa.aMotionInfo[g_Santa.motionType].aKeyInfo[g_Santa.nKey].nFrame);

		//正規化
		if (g_Santa.aModel[nCntModel].rot.x > D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.aModel[nCntModel].rot.x < -D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		//正規化
		if (g_Santa.aModel[nCntModel].rot.y > D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Santa.aModel[nCntModel].rot.y < -D3DX_PI)
		{
			g_Santa.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}
		//正規化
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
//衝突
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