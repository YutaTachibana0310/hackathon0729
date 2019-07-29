//=====================================
//
//�v���C���[�w�b�_[Player.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework\BoardPolygon.h"
#include "Framework\BoxCollider3D.h"

/**************************************
�}�N����`
***************************************/
#define PLAYER_INIT_POS				(D3DXVECTOR3(-100.0f, 0.0f, 0.0f))
#define PLAYER_POLYGON_SIZE			(D3DXVECTOR2(20.0f, 40.0f))
#define PLAYER_ATTACK_FRAME			(30)
#define PLAYTER_COLLIDER_SIZE		(D3DXVECTOR3(20.0f, 40.0f, 0.0f))
#define PLAYER_ATTACKCOLLIDER_SIZE	(D3DXVECTOR3(30.0f, 10.0f, 5.0f))

#define ATTACK_UPPER_POS			(D3DXVECTOR3(-90.0f, 30.0f, 0.0f))
#define ATTACK_MIDDLE_POS			(D3DXVECTOR3(-90.0f, 0.0f, 0.0f))
#define ATTACK_LOWER_POS			(D3DXVECTOR3(-90.0f, -30.0f, 0.0f))

#define PLAYER_INVINCBILE_FRAME		(180)

#define PLAYER_DONW_FRAME			(60)

/**************************************
�N���X��`
***************************************/
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void OnHitEnemy();

	bool isAttackNow;
	int attackFrame;		//�U���̌��ʎ���

	bool isInvincible;		//���G����
	int invincibleFrame;	//���G����

	bool isDownNow;		
	int downFrame;			//�U����̍s���s�\����

	BoxCollider3D *bodyCollider;
	BoxCollider3D *attackCollider;

private:
	BoardPolygon* polygon;
	Transform transform;

	D3DXVECTOR3 attackPos;
};

#endif