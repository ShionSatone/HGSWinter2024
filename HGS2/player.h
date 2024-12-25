//---------------------------------------
//
//���f���\�������̒�`�E�錾[player.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"
#include"stage.h"
#include"model.h"

#define PLAYER_BODY_NAME "data\\MODEL\\AKRmodel\\00_body.x"
#define PLAYER_HEAD_NAME "data\\MODEL\\AKRmodel\\01_head.x"
#define PLAYER_RIGHTARM_NAME "data\\MODEL\\AKRmodel\\02_armR.x"
#define PLAYER_RIGHTHAND_NAME "data\\MODEL\\AKRmodel\\03_handR.x"
#define PLAYER_LEFTARM_NAME "data\\MODEL\\AKRmodel\\04_armL.x"
#define PLAYER_LEFTHAND_NAME "data\\MODEL\\AKRmodel\\05_handL.x"
#define PLAYER_RIGHTLEG_NAME "data\\MODEL\\AKRmodel\\06_legR.x"
#define PLAYER_RIGHTFOOT_NAME "data\\MODEL\\AKRmodel\\07_footR.x"
#define PLAYER_LEFTLEG_NAME "data\\MODEL\\AKRmodel\\08_legL.x"
#define PLAYER_LEFTFOOT_NAME "data\\MODEL\\AKRmodel\\09_footL.x"
#define LOADPLAYER ("data\\MOTION\\model15p.txt")
#define MAX_MODEL (16)
#define NUM_MODEL (10)
#define MAX_KEY (16)
#define NUM_KEY (2)
#define MAX_MOTION (16)
#define NUM_MOTION (1)
#define SPEED (2.8f)
#define SPEED_DEF (0.0f)
#define JUMP (20.0f)
#define JUMP_INA (0.9f)
#define PLAYER_INA (0.5f)
#define ROT_SPEED (0.1f)
#define SCALE_SPEED (0.2f)
#define SCALE_MIN (0.5f)
#define SCALE_MAX (10.0f)
#define PLAYER_LIFE (1000)
#define BLEND_FRAME (10.0f)
#define PLAYER_SIZE (50.0f)
#define MODEL_SWORD (15) // ���̃��f���̃C���f�b�N�X

//�v���C���[��Ԃ̗񋓌^��`
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//�������
	PLAYERSTATE_NORMAL,//�ʏ�
	PLAYERSTATE_DAMAGE,//�_���[�W
	PLAYERSTATE_DIE,//��
	PLAYERSTATE_SLEEP,//����
	PLAYERSTATE_MAX//��
}PLAYERSTATE;

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_MOVE,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,
	MOTIONTYPE_MAX
}MOTIONTYPE;

//************************
// ���[�V�����̏��
//************************
typedef enum
{
	MOTIONSTATE_NEUTRAL = 0,//�j���[�g����
	MOTIONSTATE_MOVE,       //�������[�V����
	MOTIONSTATE_ACTION,     //�U�����[�V����
	MOTIONSTATE_MAX
}MOTIONSTATE;

//�L�[�̍\����
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;
	KEY aKey[MAX_MODEL];
}KEY_INFO;

typedef struct
{
	bool bLoop;
	int nNumKey;
	KEY_INFO aKeyInfo[MAX_KEY];
}MOTION_INFO;

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 scale;
	bool bJump;
	int nLife;
	PLAYERSTATE state;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
	int nIdxLife;
	Model aModel[MAX_MODEL];
	int nNumModel;
	MOTION_INFO aMotionInfo[MAX_MOTION];
	int nNumMotion;
	MOTIONTYPE motionType;
	bool bLoopMotion;
	int nNumKey;
	int nKey;
	int nCounterMotion;
	Stage* pStage;
	bool bUse;
	MOTIONSTATE motionstate; // ���[�V�����̏��
	float PlayerMove;//�v���C���[�̈ړ���
	int nCounterstate; // �v���C���[�̏�ԃJ�E���^�[
	D3DXVECTOR3 SwordOffpos;//���̉ˋ�̈ʒu�̊
	D3DXMATRIX SwordMtxWorld;//���̐�̃��[���h�}�g���b�N�X
	D3DXVECTOR3 Size;//�v���C���[�̃T�C�Y
}Player;

void InitPlayer(void);//�|���S���̏���������
void UninitPlayer(void);//�|���S���̏I������
void UpdatePlayer(void);//�|���S���̍X�V����
void DrawPlayer(void);//�|���S���̕`�揈��
void SetWorldMtx(void);//���̃��[���h�}�g���b�N�X�ݒ�p�֐�
Player* GetPlayer(void);
bool CollisionSword(D3DXVECTOR3 pos);//�T���^�ƌ��̓����蔻��
void CollisionObj(D3DXVECTOR3 pos, D3DXVECTOR3 Size);

void UpdateMotion(void);
void CollisionPlayer(D3DXVECTOR3 pos, float Length);
void LoadPlayer(void);//�v���C���[�̓ǂݍ��ݏ���
#endif _PLAYER_H_