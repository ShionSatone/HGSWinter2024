//----------------------------------------
//
//モデル表示処理[player.cpp]
//Author fuma sato
//
//----------------------------------------

//****************************************
// インクルードファイル
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
#include "bed.h"
#include "santa.h"
#include "effect.h"
#include "score.h"
#include "blacksanta.h"

//****************************************
// マクロ定義
//****************************************
#define MAX_WORD (128) // 最大の文字数
#define NUM_SWORDPOS (4) // 剣の位置の数

//****************************************
// グローバル変数
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
//ポリゴンの初期化処理
//----------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
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
	g_Player.motionstate = MOTIONSTATE_NEUTRAL; // モーションの状態
	g_Player.PlayerMove = 0.0f; // プレイヤーの移動量
	g_Player.nCounterstate = 0; // プレイヤーの状態カウンター
	g_Player.SwordOffpos = D3DXVECTOR3(0.0f, 85.0f, 0.0f);//剣の先の基準の位置

	LoadModel();
	LoadPlayer();// プレイヤーのロード処理

	int nCntModel;

	for (nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャがある
				//テクスチャの読み込み
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Player.aModel[nCntModel].apTexture[nCntMat]
				);
			}
		}

		//頂点数
		g_Player.aModel[nCntModel].nNumVtx = g_Player.aModel[nCntModel].pMesh->GetNumVertices();
		//頂点サイズ
		g_Player.aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMesh->GetFVF());
		//頂点バッファの取得
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

	//全モデルの大きさを設定する
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		g_Player.aModel[nCntModel].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//大きさを設定
	}

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		g_Player.aModel[nCnt].posDef = g_Player.aModel[nCnt].pos;
	}

	g_Player.nIdxShadow = SetShadow(g_Player.pos, g_Player.rot);
	g_Player.nIdxLife = LinkLife();
}

//-------------------
//ポリゴン終了処理
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
		//メッシュの破棄
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdatePlayer(void)
{
	Santa* pSanta = GetSanta();
	BlackSanta* pBlackSnata = GetBlackSanta();

	if (g_Player.bUse)
	{
		Camera* pCamera = GetCamera();
		float* pStick;
		bool bUsePad = false; //パッドを使用しているか
		//X
		if (IsXInputControllerConnected(CONTROLLER_1)&& g_Player.motionType != MOTIONTYPE_ACTION)
		{
			//左スティック処理
			pStick = GetJoyStick(STICK_LEFT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f + -atan2f(*(pStick + 1), *pStick);
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
					bUsePad = true;
				}
			}
		}

//************************************************
// プレイヤーの移動処理
//************************************************

		if (g_Player.motionType != MOTIONTYPE_ACTION)
		{
			//左斜め移動
			if (GetKeyboradPress(DIK_A) == true)
			{
				//プレイヤーの移動(上)
				if (GetKeyboradPress(DIK_W) == true)
				{
					g_Player.motionType = MOTIONTYPE_MOVE; // モーションを歩きモーションにする

					g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * g_Player.PlayerMove;
					g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * g_Player.PlayerMove;

					g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.75f; // プレイヤーの向きを上向きにする
				}
				//プレイヤーの移動(下)
				else if (GetKeyboradPress(DIK_S) == true)
				{
					g_Player.motionType = MOTIONTYPE_MOVE; // モーションを歩きモーションにする

					g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * g_Player.PlayerMove;
					g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * g_Player.PlayerMove;

					g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.25f; // プレイヤーの向きを下向きにする
				}
				//プレイヤーの移動(左)
				else
				{
					g_Player.motionType = MOTIONTYPE_MOVE; // モーションを歩きモーションにする

					g_Player.move.z += sinf(pCamera->rot.y) * g_Player.PlayerMove;
					g_Player.move.x -= cosf(pCamera->rot.y) * g_Player.PlayerMove;

					g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.5f; // プレイヤーの向きを左向きにする
				}
			}
			//右斜め移動
			else if (GetKeyboradPress(DIK_D) == true)
			{
				//プレイヤーの移動(上)
				if (GetKeyboradPress(DIK_W) == true)
				{
					g_Player.motionType = MOTIONTYPE_MOVE; // モーションを歩きモーションにする

					g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * g_Player.PlayerMove;
					g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * g_Player.PlayerMove;

					g_Player.Destrot.y = pCamera->rot.y - D3DX_PI * 0.75f; // プレイヤーの向きを上向きにする
				}
				//プレイヤーの移動(下)
				else if (GetKeyboradPress(DIK_S) == true)
				{
					g_Player.motionType = MOTIONTYPE_MOVE; // モーションを歩きモーションにする

					g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * g_Player.PlayerMove;
					g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * g_Player.PlayerMove;

					g_Player.Destrot.y = pCamera->rot.y - D3DX_PI * 0.25f; // プレイヤーの向きを下向きにする
				}
				//プレイヤーの移動(右)
				else
				{
					g_Player.motionType = MOTIONTYPE_MOVE; // モーションを歩きモーションにする

					g_Player.move.z -= sinf(pCamera->rot.y) * g_Player.PlayerMove;
					g_Player.move.x += cosf(pCamera->rot.y) * g_Player.PlayerMove;

					g_Player.Destrot.y = pCamera->rot.y - D3DX_PI * 0.5f; // プレイヤーの向きを右向きにする
				}

			}
			//プレイヤーの移動(上)
			else if (GetKeyboradPress(DIK_W) == true)
			{
				g_Player.motionType = MOTIONTYPE_MOVE; // モーションを歩きモーションにする

				g_Player.move.x += sinf(pCamera->rot.y) * g_Player.PlayerMove;
				g_Player.move.z += cosf(pCamera->rot.y) * g_Player.PlayerMove;

				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI; // 上向き
			}
			//プレイヤーの移動(下)
			else if (GetKeyboradPress(DIK_S) == true)
			{
				g_Player.motionType = MOTIONTYPE_MOVE; // モーションを歩きモーションにする

				g_Player.move.x -= sinf(pCamera->rot.y) * g_Player.PlayerMove;
				g_Player.move.z -= cosf(pCamera->rot.y) * g_Player.PlayerMove;

				g_Player.Destrot.y = pCamera->rot.y; // 下向き
			}
			else
			{
				if (bUsePad == false && g_Player.motionType != MOTIONTYPE_ACTION)//パッドが使用されていなかったら
				{
					g_Player.motionType = MOTIONTYPE_NEUTRAL; // キーが押されてない時プレイヤーのモーションをニュートラルにする
				}
			}
		}
	}

	if (GetKeyboradTrigger(DIK_RETURN) == true||GetJoykeyTrigger(JOYKEY_RT, CONTROLLER_1)==true)
	{
		if (g_Player.motionType != MOTIONTYPE_ACTION)
		{
			g_Player.nKey = 0;//キーを0番目から始める
			g_Player.motionType = MOTIONTYPE_ACTION;
		}
	}

	//モーションの状態
	switch (g_Player.motionstate)
	{
	case MOTIONSTATE_NEUTRAL:
		break;
	case MOTIONSTATE_MOVE:

		break;
	case MOTIONSTATE_ACTION:

		break;
	default:
		break;
	}

	//前回の位置を保存
	g_Player.posOld = g_Player.pos;

	//位置の更新
	g_Player.pos += g_Player.move;

	//移動量の更新(減衰)
	g_Player.move.x += (SPEED_DEF - g_Player.move.x) * PLAYER_INA;
	g_Player.move.z += (SPEED_DEF - g_Player.move.z) * PLAYER_INA;

	g_Player.pStage = NULL;

	CollisionSnowBall(g_Player.pos, PLAYER_SIZE);

	g_Player.bJump = !CollisionStage(&g_Player.pStage);


	//サンタと剣の当たり判定
	if (CollisionSword(pSanta->pos) == true && pSanta->bUse==true)
	{
		pSanta->bUse = false;//サンタの使用状態をfalseにする
		AddScore(-1);
	}
	else if (CollisionSword(pBlackSnata->pos) == true && pBlackSnata->bUse == true)
	{
		pBlackSnata->bUse = false;//ブラックサンタの使用状態をfalseにする
	}

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

	//正規化
	if (g_Player.Destrot.y > D3DX_PI)
	{
		g_Player.Destrot.y -= D3DX_PI * 2.0f;
	}
	else if (g_Player.Destrot.y < -D3DX_PI)
	{
		g_Player.Destrot.y += D3DX_PI * 2.0f;
	}

	//正規化
	if (g_Player.Destrot.y - g_Player.rot.y > D3DX_PI)
	{
		g_Player.Destrot.y = g_Player.rot.y + ((g_Player.Destrot.y - g_Player.rot.y) - D3DX_PI * 2.0f);
	}
	else if (g_Player.Destrot.y - g_Player.rot.y < -D3DX_PI)
	{
		g_Player.Destrot.y = g_Player.rot.y + ((g_Player.Destrot.y - g_Player.rot.y) + D3DX_PI * 2.0f);
	}

	g_Player.rot.y += (g_Player.Destrot.y - g_Player.rot.y) * ROT_SPEED;

	//正規化
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2.0f;
	}

	//正規化
	if (g_Player.Destrot.x > D3DX_PI)
	{
		g_Player.Destrot.x -= D3DX_PI * 2.0f;
	}
	else if (g_Player.Destrot.x < -D3DX_PI)
	{
		g_Player.Destrot.x += D3DX_PI * 2.0f;
	}

	//正規化
	if (g_Player.Destrot.x - g_Player.rot.x > D3DX_PI)
	{
		g_Player.Destrot.x = g_Player.rot.x + ((g_Player.Destrot.x - g_Player.rot.x) - D3DX_PI * 2.0f);
	}
	else if (g_Player.Destrot.x - g_Player.rot.x < -D3DX_PI)
	{
		g_Player.Destrot.x = g_Player.rot.x + ((g_Player.Destrot.x - g_Player.rot.x) + D3DX_PI * 2.0f);
	}

	g_Player.rot.x += (g_Player.Destrot.x - g_Player.rot.x) * ROT_SPEED;

	//正規化
	if (g_Player.rot.x > D3DX_PI)
	{
		g_Player.rot.x -= D3DX_PI * 2.0f;
	}
	else if (g_Player.rot.x < -D3DX_PI)
	{
		g_Player.rot.x += D3DX_PI * 2.0f;
	}

	//スケール制限
	g_Player.scale.x = max(SCALE_MIN, min(SCALE_MAX, g_Player.scale.x));
	g_Player.scale.y = max(SCALE_MIN, min(SCALE_MAX, g_Player.scale.y));
	g_Player.scale.z = max(SCALE_MIN, min(SCALE_MAX, g_Player.scale.z));

	int nCntModel;
	//パーツ分回す
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

	Bed* pBed = GetBed();

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
	case PLAYERSTATE_SLEEP:		// 睡眠

		// プレイヤーの位置更新
		g_Player.pos = D3DXVECTOR3(pBed->pos.x, pBed->pos.y + 30.0f, pBed->pos.z - 20.0f);

		// 向き更新
		g_Player.rot = D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f);
		break;

	case PLAYERSTATE_DIE:
		g_Player.Destrot.x = D3DX_PI * 0.5f;
		static int nCnt = 0;
		nCnt++;
		if (nCnt >= 20)
		{
			NullShadow(g_Player.nIdxShadow);
			NullLife(g_Player.nIdxLife);
			SetParticle(g_Player.pos, g_Player.scale,PARTICLE_TYPE_NONE);
			g_Player.state = PLAYERSTATE_APPEAR;
		}
		break;
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawPlayer(void)
{
	if (g_Player.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
		D3DMATERIAL9 matDef;//現在のマテリアル保存用
		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ


		//デバイスの取得
		pDevice = GetDevice();

		//マトリックス初期化
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		//大きさの反映
		D3DXMatrixScaling(&mtxScale, g_Player.scale.x, g_Player.scale.y, g_Player.scale.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScale);

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

		int nCntModel;
		//パーツ分回す
		for (nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//計算マトリックス
			D3DXMATRIX mtxParent;
			//マトリックス初期化
			D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

			//大きさの反映
			D3DXMatrixScaling(&mtxScaleModel, g_Player.aModel[nCntModel].scale.x, g_Player.aModel[nCntModel].scale.y, g_Player.aModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxScaleModel);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置の反映
			D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスの設定
			if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
			{//親モデルがある
				mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//親モデルがない
				mtxParent = g_Player.mtxWorld;
			}

			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャ
				pDevice->SetTexture(0, g_Player.aModel[nCntModel].apTexture[nCntMat]);

				//モデル描画
				g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			if (nCntModel == 15)
			{
				SetWorldMtx();//剣のモデルの位置の反映が終わったら剣先のワールドマトリックスを設定
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//======================================
// 剣の先のワールドマトリックスの設定用
//======================================
void SetWorldMtx(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans,mtxParent;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	//マトリックス初期化
	D3DXMatrixIdentity(&g_Player.SwordMtxWorld);

	//向きの反映(向きをモデル剣の向きにする)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[MODEL_SWORD].rot.y,
		g_Player.aModel[MODEL_SWORD].rot.x,
		g_Player.aModel[MODEL_SWORD].rot.z);

	D3DXMatrixMultiply(&g_Player.SwordMtxWorld, &g_Player.SwordMtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.SwordOffpos.x, g_Player.SwordOffpos.y, g_Player.SwordOffpos.z);
	D3DXMatrixMultiply(&g_Player.SwordMtxWorld, &g_Player.SwordMtxWorld, &mtxTrans);

	mtxParent = g_Player.aModel[MODEL_SWORD].mtxWorld; //親を設定

	//親のワールドマトリックスと自分のワールドマトリックスをかけ合わせる
	D3DXMatrixMultiply(&g_Player.SwordMtxWorld,
		&g_Player.SwordMtxWorld,
		&mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.SwordMtxWorld);
}

//------------------------------
//位置取得
//------------------------------
Player* GetPlayer(void)
{
	return &g_Player;
}
//======================================
// サンタと剣の判定
//======================================
bool CollisionSword(D3DXVECTOR3 pos)
{
	bool bHit = false; // 当たっているかどうか

	float fSwordDisX, fSwordDisY, fSwordDisZ; //剣の位置設定用変数
	float fSwordPosX, fSwordPosY, fSwordPosZ; //剣の位置用変数

	float fDistanseX, fDistanseY, fDistanseZ, fDistanse; //距離X,Y,Z,距離代入用変数
	float fRadius;//半径用変数

	fSwordDisX = g_Player.SwordMtxWorld._41 - g_Player.aModel[MODEL_SWORD].mtxWorld._41; // 剣の根元から剣の先までの距離Xを求める
	fSwordDisY = g_Player.SwordMtxWorld._42 - g_Player.aModel[MODEL_SWORD].mtxWorld._42; // 剣の根元から剣の先までの距離Yを求める
	fSwordDisZ = g_Player.SwordMtxWorld._43 - g_Player.aModel[MODEL_SWORD].mtxWorld._43; // 剣の根元から剣の先までの距離Zを求める

	//剣の当たり判定の位置を設定
	for (int nCntSwordPos = 0; nCntSwordPos < NUM_SWORDPOS; nCntSwordPos++)
	{
		//剣の当たり判定の位置を算出
		fSwordPosX = g_Player.aModel[MODEL_SWORD].mtxWorld._41 + fSwordDisX * 0.25f * nCntSwordPos;
		fSwordPosY = g_Player.aModel[MODEL_SWORD].mtxWorld._42 + fSwordDisY * 0.25f * nCntSwordPos;
		fSwordPosZ = g_Player.aModel[MODEL_SWORD].mtxWorld._43 + fSwordDisZ * 0.25f * nCntSwordPos;

		//距離XYZを求める
		fDistanseX = pos.x - fSwordPosX;
		fDistanseY = pos.y - fSwordPosY;
		fDistanseZ = pos.z - fSwordPosZ;

		fDistanse = (fDistanseX * fDistanseX) + (fDistanseY * fDistanseY) + (fDistanseZ * fDistanseZ);//距離を求める

		float fSwordRadius = 20.0f; // 剣の半径
		float fSantaRadius = 20.0f; //サンタの半径

		fRadius = fSwordRadius + fSantaRadius;//半径を求める
		fRadius = fRadius * fRadius;

//#ifdef _DEBUG
//		SetEffect(D3DXVECTOR3(fSwordPosX, fSwordPosY, fSwordPosZ),
//			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
//			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
//			D3DXVECTOR3(1.0f, 1.0f, 1.0f),
//			10,
//			EFFECT_TYPE_NORMAL);
//#endif

		if (fDistanse <= fRadius && g_Player.motionType == MOTIONTYPE_ACTION)
		{
			bHit = true;//剣がサンタに当たった
		}
	}
	
	return bHit;//ヒット判定を返す
}

//------------------------------
//モーション
//------------------------------
void UpdateMotion(void)
{
	int nextKey = 0;//次のキー

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		float DiffPosX, DiffPosY, DiffPosZ, DiffRotX, DiffRotY, DiffRotZ; //位置の差、向きの差を求める変数

		DiffPosX = DiffPosY = DiffPosZ = DiffRotX = DiffRotY = DiffRotZ = 0.0f; //変数を初期化

		nextKey = (g_Player.nKey + 1) % g_Player.aMotionInfo[g_Player.motionType].nNumKey;//次のキーを計算

		//位置の差、向きの差を求める
		DiffPosX = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fPosX - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX;
		DiffPosY = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fPosY - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY;
		DiffPosZ = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fPosZ - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ;
		DiffRotX = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fRotX - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX;
		DiffRotY = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fRotY - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY;
		DiffRotZ = g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nextKey].aKey[nCntModel].fRotZ - g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ;

		//パーツの位置Xを設定
		g_Player.aModel[nCntModel].pos.x =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX +
			DiffPosX *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//パーツの位置Yを設定
		g_Player.aModel[nCntModel].pos.y =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY +
			DiffPosY *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//パーツの位置Zを設定
		g_Player.aModel[nCntModel].pos.z =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ +
			DiffPosZ *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//パーツの向きXを設定
		g_Player.aModel[nCntModel].rot.x =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX +
			DiffRotX *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//パーツの向きYを設定
		g_Player.aModel[nCntModel].rot.y =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY +
			DiffRotY *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//パーツの向きZを設定
		g_Player.aModel[nCntModel].rot.z =
			g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ +
			DiffRotZ *
			((float)g_Player.nCounterMotion /
				(float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//オフセットと足す
		g_Player.aModel[nCntModel].rot += g_Player.aModel[nCntModel].offrot;
		g_Player.aModel[nCntModel].pos += g_Player.aModel[nCntModel].offpos;

		//カウンターモーションが最大まで行ったら0に戻す
		if (g_Player.nCounterMotion >= g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame)
		{
			g_Player.nKey = (g_Player.nKey + 1) % g_Player.aMotionInfo[g_Player.motionType].nNumKey;
			g_Player.nCounterMotion = 0;
		}

		//モーションのループがfalseだったら
		if (g_Player.aMotionInfo[g_Player.motionType].bLoop == false && g_Player.nKey >= g_Player.aMotionInfo[g_Player.motionType].nNumKey - 1)
		{
			g_Player.motionType = MOTIONTYPE_NEUTRAL;//モーションをニュートラルにする
		}
	}
	g_Player.nCounterMotion++;
}

//------------------------------------------------
//衝突
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
// プレイヤーの読み込み処理
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
			char aStr[MAX_WORD];//文字読み込み用変数

			fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(aStr, "SCRIPT") == 0)
			{//読み取った文字がSCRIPTだったら

				while (1)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strcmp(aStr, "NUM_MODEL") == 0)
					{
						//読み取った文字がNUM_MODELだったら

						fscanf(pFile, "%s", &skip[0]); //[=]を読み飛ばす
						fscanf(pFile, "%d", &nNumModel); //モデルの数を読み込む変数に代入
					}
					else if (strcmp(aStr, "MODEL_FILENAME") == 0)
					{//読み取った文字がMODEL_FILENAMEだったら

						fscanf(pFile, "%s", &skip[0]);
						fscanf(pFile, "%s", &aStr[0]);

						const char* FILE_NAME = {}; //ファイルの名前を格納する変数

						FILE_NAME = aStr; // 読み取ったファイルの名前を代入

						//モデルを読み込む
						D3DXLoadMeshFromX(FILE_NAME,
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_Player.aModel[nCnt].pBuffMat,
							NULL,
							&g_Player.aModel[nCnt].dwNumMat,
							&g_Player.aModel[nCnt].pMesh);

						nCnt++;//モデルのカウントを増やす
					}
					else if (strcmp(aStr, "CHARACTERSET") == 0)
					{//読み取った文字がCHARACTERSETだったら
						while (1)
						{
							fscanf(pFile, "%s", &aStr[0]);

							if (strcmp(aStr, "NUM_PARTS") == 0)
							{//読み取った文字がNUM_PARTSだったら

								fscanf(pFile, "%s", &skip[0]);//[=]を読み飛ばす
								fscanf(pFile, "%d", &g_Player.nNumModel);//モデルの最大数を代入
							}
							else if (strcmp(aStr, "MOVE") == 0)
							{// 読み取った文字がMOVEだったら

								fscanf(pFile, "%s", &skip[0]);// [=]を読み飛ばす

								fscanf(pFile, "%f", &g_Player.PlayerMove);//プレイヤーの移動量を代入
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
