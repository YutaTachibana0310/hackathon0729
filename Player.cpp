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


	//�����蔻�萶��
	bodyCollider = new BoxCollider3D(BoxCollider3DTag::Player, &transform.pos);
	bodyCollider->SetSize(PLAYTER_COLLIDER_SIZE);
	bodyCollider->active = true;

	attackCollider = new BoxCollider3D(BoxCollider3DTag::PlayerAttack, &attackPos);
	attackCollider->SetSize(PLAYER_ATTACKCOLLIDER_SIZE);
	attackCollider->active = false;
	
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
	transform.pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	
	isAttackNow = false;
	attackFrame = 0;
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

	//�U������
	if (!isAttackNow)
	{
		//��i�U��
		if (GetKeyboardTrigger(DIK_Z))
		{
			attackPos = ATTACK_UPPER_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
		}
		//���i�U��
		else if (GetKeyboardTrigger(DIK_X))
		{
			attackPos = ATTACK_MIDDLE_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
		}
		//���i�U��
		else if (GetKeyboardTrigger(DIK_C))
		{
			attackPos = ATTACK_LOWER_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
		}
	}

	//�U������̍X�V
	if (isAttackNow)
	{
		attackFrame++;
		if (attackFrame == PLAYER_ATTACK_FRAME)
		{
			isAttackNow = false;
			attackCollider->active = false;
		}
	}
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

	//�����蔻��`��
	BoxCollider3D::DrawCollider(bodyCollider);
	BoxCollider3D::DrawCollider(attackCollider);
}
