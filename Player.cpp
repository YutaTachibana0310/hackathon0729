//=====================================
//
//�v���C���[����[Player.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Player.h"
#include "Framework\ResourceManager.h"
#include "input.h"

/**************************************
�}�N����`
***************************************/
#define PLAYER_MOVE_SPEED	(1.0f)

/**************************************
�R���X�g���N�^
***************************************/
Player::Player()
{
	//�|���S�������\�[�X�}�l�[�W������擾
	ResourceManager::Instance()->GetPolygon("Sample", &polygon);
}

/**************************************
�f�X�g���N�^
***************************************/
Player::~Player()
{
	//�������̉���̓��\�[�X�}�l�[�W���ɔC����̂ŎQ�Ƃ���߂邾��
	polygon = NULL;
}

/**************************************
����������
***************************************/
void Player::Init()
{

}

/**************************************
�I������
***************************************/
void Player::Uninit()
{

}

/**************************************
�X�V����
***************************************/
void Player::Update()
{
	//�ړ�����
	D3DXVECTOR3 direction;
	ZeroMemory(&direction, sizeof(direction));

	//���͂ňړ�����������
	direction.x = GetHorizontalInputPress();
	direction.y = GetVerticalInputPress();

	//���K�����Ĉړ�
	D3DXVec3Normalize(&direction, &direction);
	transform.pos += direction * PLAYER_MOVE_SPEED;
}

/**************************************
�`�揈��
***************************************/
void Player::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���[���h�ϊ��s��̌v�Z�iTransform�\���̂ɔC����j
	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//�`��
	polygon->Draw();
}
