//------------------------------------------
//
//�Q�[�����C���̏���[game.cpp]
//Author fuma sato
//
//------------------------------------------

#include"game.h"
#include"input.h"
#include"player.h"
#include"bullet.h"
#include"effect.h"
#include"particle.h"
#include"model.h"
#include"pause.h"
#include"time.h"
#include"fade.h"
#include"sound.h"
#include"score.h"
#include"camera.h"
#include"life.h"
#include"hitshere.h"
#include"snow.h"
#include"ui.h"
#include "present.h"
#include"santa.h"
#include"blacksanta.h"
#include "bed.h"
#include "socks.h"
#include "window.h"

#include"shadow.h"
#include"billboard.h"
#include"stage.h"
#include"file.h"
#include"meshfield.h"
#include"cylinder.h"
#include"sphere.h"
#include"meshwall.h"
#include"snowball.h"
#include "chimney.h"
#include "door.h"
#include "meshorbit.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_GameTime = 0;
int g_SantaCount = 0;
int g_SantaTime = 0;
bool g_bSnow = false;
bool g_bClear = false;
//--------------------
//����������
//--------------------
void InitGame(void)
{
	InitModel();
	InitShadow();
	InitLife();
	InitStage();
	InitMeshField();
	InitCylinder();
	InitSphere();
	InitSnowBall();
	InitMeshWall();
	InitPlayer();//�v���C���[
	InitSanta();
	InitBlackSanta();
	InitBullet();
	InitEffect();
	InitParticle();
	InitSnow();
	InitBillboard();
	InitScore();
	InitTime();
	InitUi();
	InitHitShere();
	InitPresent();		// �v���[���g
	InitBed();			// �x�b�h
	InitChimney();      //���˂̏���������
	InitDoor();      //�h�A�̏���������
	InitSocks();		// �C��
	InitWindow();		// ��
	InitMeshSword();    //���̋O���̏���������

	//���
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�X�e�[�W
	LoadStage();

	D3DXVECTOR3 posScore;//�X�R�A�̈ʒu
	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_GameTime = 0;
	g_bSnow = false;
	g_bClear = false;

	PlaySound(SOUND_LABEL_BGM);

	SetScore(0, true);
}

//------------------
//�I������
//------------------
void UninitGame(void)
{
	g_gameState = GAMESTATE_NONE;
	EndSound();

	UninitHitShere();
	UninitUi();
	UninitTime();
	UninitScore();
	UninitSnow();
	UninitParticle();
	UninitEffect();
	UninitBullet();
	UninitBillboard();
	UninitMeshWall();
	UninitCylinder();
	UninitSnowBall();
	UninitSphere();
	UninitMeshField();
	UninitBlackSanta();
	UninitSanta();
	UninitPlayer();//�v���C���[
	UninitStage();
	UninitLife();
	UninitShadow();
	UninitModel();
	UninitPresent();		// �v���[���g
	UninitBed();			// �x�b�h
	UninitChimney();      //���˂̏I������
	UninitDoor();      //�h�A�̏I������
	UninitSocks();		// �C��
	UninitWindow();		// ��
	UninitMeshSword();    //���̋O���̏I������
}

//--------------
//�X�V����
//--------------
void UpdateGame(void)
{
	if (GetKeyboradTrigger(DIK_P) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_SENTER) == true)
	{
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			Pause(SOUND_LABEL_BGM);
		}
	}
	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM);
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_�{, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM);
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM);
			}
		}
	}
	
	if (!bPause())
	{
		Player* pPlayer;

		pPlayer = GetPlayer();

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			g_GameTime++;
			SetTime(TIME_LIMIT - (int)(g_GameTime / (float)FRAME), true);
			if (g_GameTime / FRAME >= TIME_LIMIT)
			{
				g_gameState = GAMESTATE_END;
				g_bClear = true;
			}
			else if (pPlayer->state == PLAYERSTATE_DIE)
			{
				g_gameState = GAMESTATE_END;
				g_bClear = false;
			}
			else if (GetKeyboradTrigger(DIK_0))
			{
#ifdef _DEBUG
				g_gameState = GAMESTATE_END;
				g_bClear = false;
#endif
			}

			Santa* pSanta;
			pSanta = GetSanta();
			BlackSanta* pBlackSanta;
			pBlackSanta = GetBlackSanta();
			if (!pSanta->bUse && !pBlackSanta->bUse)
			{
				if (g_SantaCount == 0)
				{
					switch (rand() % PATA_MAX)
					{
					case PATA1:
						g_SantaTime = PATA1_TIME;
						break;
					case PATA2:
						g_SantaTime = PATA2_TIME;
						break;
					case PATA3:
						g_SantaTime = PATA3_TIME;
						break;
					}
				}
				g_SantaCount++;

				if (g_SantaCount / FRAME >= g_SantaTime)
				{
					D3DXVECTOR3 pos;
					switch (rand() % PATA_MAX)
					{
					case PATA1:
						Door* pDoor;
						pDoor = GetDoor();
						pos = pDoor->pos;
						break;
					case PATA2:
						Chimney* pChimney;
						pChimney = GetChimney();
						pos = pChimney->pos;
						break;
					case PATA3:
						pos = D3DXVECTOR3(0.0f,50.0f,-20.0f);
						break;
					}

					if (pPlayer->state == PLAYERSTATE_SLEEP)
					{
						switch (rand() % 2)
						{
						case 0:
							SetSanta(pos);
							break;
						case 1:
							SetBlackSanta(pos);
							break;
						}
					}
					else
					{
						SetBlackSanta(pos);
					}
				}
			}
			else
			{
				g_SantaCount = 0;
			}
			break;
		case GAMESTATE_END:
			g_nCounterGameState++;
			if (g_nCounterGameState >= INTER)
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�T�E���h
					StopSound(SOUND_LABEL_BGM4);
					//�ؑ�
					SetFade(MODE_RESULT);
				}
			}
			break;
		}

		UpdateModel();
		UpdateShadow();
		UpdateLife();
		UpdateStage();
		UpdatePlayer();//�v���C���[
		UpdateSanta();
		UpdateBlackSanta();
		UpdateHitShere();
		UpdateMeshWall();
		UpdateMeshField();
		UpdateCylinder();
		UpdateSphere();
		UpdateSnowBall();
		UpdateBillboard();
		UpdateBullet();
		UpdateEffect();
		UpdateParticle();
		UpdateScore();
		UpdateSnow();
		UpdateUi();
		UpdatePresent();
		UpdateBed();			// �x�b�h
		UpdateChimney();      //���˂̍X�V����
		UpdateDoor();      //�h�A�̍X�V����
		UpdateSocks();		// �C��
		UpdateWindow();		// ��
		UpdateMeshSword();    //���̋O���̍X�V����
	}
}

//-------------------
//�`�揈��
//-------------------
void DrawGame(void)
{
	DrawModel();
	DrawMeshField();
	DrawCylinder();
	DrawSphere();
	DrawShadow();
	DrawStage();
	DrawBillboard();
	DrawMeshWall();
	DrawEffect();
	DrawBullet();
	DrawSnowBall();
	DrawPlayer();//�v���C���[
	DrawSanta();
	DrawBlackSanta();
	DrawHitShere();
	DrawAlphaMeshWall();
	DrawLife();
	DrawScore();
	DrawTime();
	DrawUi();
	DrawPresent();
	DrawBed();			// �x�b�h
	DrawChimney();      //���˂̕`�揈��
	DrawDoor();      //�h�A�̕`�揈��
	DrawSocks();		// �C��
	DrawWindow();		// ��
	DrawMeshSword();    //���̋O���̕`�揈��
}

//----------------------
//�Q�[����Ԑؑ�
//----------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//-----------------------
//�Q�[����Ԏ擾
//-----------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//-----------------------
//�X�m�[�擾
//-----------------------
bool GetbSnow(void)
{
	return g_bSnow;
}

//---------------------
//�N���A�擾
//---------------------
bool GetClear(void)
{
	return g_bClear;
}

//---------------------
//�N���A�擾
//---------------------
int GetClearTime(void)
{
	int H = (((g_GameTime / FRAME) * (int)(HOUR * ((float)MINUTE / (float)TIME_LIMIT))) / MINUTE) * 100;
	int M = ((g_GameTime / FRAME) * (int)(HOUR * ((float)MINUTE / (float)TIME_LIMIT))) % MINUTE;
	return H + M;
}

//---------------------
//�N���A�擾
//---------------------
int GetTime(void)
{
	return g_GameTime / FRAME;
}

//---------------------
//���ԏ�����
//---------------------
void TimeReset(void)
{
	g_GameTime = 0;
}