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
	polygonContainer.resize(PlayerTextureMax);
	//�|���S�������\�[�X�}�l�[�W������擾
	ResourceManager::Instance()->GetPolygon("Player", &polygonContainer[PlayerStand]);
	ResourceManager::Instance()->GetPolygon("PlayerUpper", &polygonContainer[PlayerUpper]);
	ResourceManager::Instance()->GetPolygon("PlayerMiddle", &polygonContainer[PlayerMiddle]);
	ResourceManager::Instance()->GetPolygon("PlayerLower", &polygonContainer[PlayerLower]);
	ResourceManager::Instance()->GetPolygon("PlayerDown", &polygonContainer[PlayerDown]);

	//�����蔻�萶��
	bodyCollider = new BoxCollider3D(BoxCollider3DTag::Player, &transform.pos);
	bodyCollider->SetSize(PLAYTER_COLLIDER_SIZE);
	bodyCollider->active = true;

	attackCollider = new BoxCollider3D(BoxCollider3DTag::PlayerAttack, &attackPos);
	attackCollider->SetSize(PLAYER_ATTACKCOLLIDER_SIZE);
	attackCollider->active = false;


	isAttackNow = false;
	attackFrame = 0;

	isInvincible = false;
	invincibleFrame = 0;

	isDownNow = false;
	downFrame = 0;
}

/**************************************
�f�X�g���N�^
***************************************/
Player::~Player()
{
	//�������̉���̓��\�[�X�}�l�[�W���ɔC����̂ŎQ�Ƃ���߂邾��
	for (auto& polygon : polygonContainer)
	{
		polygon = NULL;
	}
}

/**************************************
����������
***************************************/
void Player::Init()
{
	transform.pos = PLAYER_INIT_POS;

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
	if (!isAttackNow && !isDownNow)
	{
		//��i�U��
		if (GetKeyboardTrigger(DIK_Z))
		{
			attackPos = ATTACK_UPPER_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
			textureID = PlayerUpper;
		}
		//���i�U��
		else if (GetKeyboardTrigger(DIK_X))
		{
			attackPos = ATTACK_MIDDLE_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
			textureID = PlayerMiddle;
		}
		//���i�U��
		else if (GetKeyboardTrigger(DIK_C))
		{
			attackPos = ATTACK_LOWER_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
			textureID = PlayerLower;
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
			textureID = PlayerStand;
		}
	}

	//���G���Ԃ̍X�V
	if (isInvincible && !isDownNow)
	{
		invincibleFrame++;
		if (invincibleFrame == PLAYER_INVINCBILE_FRAME)
		{
			isInvincible = false;
			bodyCollider->active = true;
		}
	}

	//�s���s�\���Ԃ̍X�V
	if (isDownNow)
	{
		downFrame++;
		if (downFrame == PLAYER_DONW_FRAME)
		{
			isDownNow = false;
			textureID = PlayerStand;
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
	polygonContainer[textureID]->Draw();

	//�����蔻��`��
	BoxCollider3D::DrawCollider(bodyCollider);
	BoxCollider3D::DrawCollider(attackCollider);
}

/**************************************
�G�l�~�[�Ƃ̏Փˏ���
***************************************/
void Player::OnHitEnemy()
{
	downFrame = 0;
	isDownNow = true;

	isInvincible = true;
	invincibleFrame = 0;

	textureID = PlayerDown;
}