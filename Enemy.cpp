#include "main.h"
#include "Enemy.h"
#include "Framework\ResourceManager.h"
#include "GameScene.h"
#include "GameSceneParticleManager.h"
#include "GameParameter.h"
#include "soundEffectManager.h"

#define ENEMY_SPEED	D3DXVECTOR3(-3.0f, 0.0f, 0.0f)
#define ENEMY_POINT			(10)

Enemy::Enemy(int num)
{
	//ポリゴンをリソースマネージャから取得
	ResourceManager::Instance()->GetPolygon("Enemy", &polygon);

	// 当たり判定生成
	bodyCollider = new BoxCollider3D(BoxCollider3DTag::Enemy, &transform.pos);
	bodyCollider->SetSize(ENEMY_COLLIDER_SIZE);
	bodyCollider->active = true;

	// 座標セット
	switch (num)
	{
	case 0:
		this->transform.pos = START_HIGH;
		break;
	case 1:
		this->transform.pos = START_MIDDLE;
		break;
	case 2:
		this->transform.pos = START_LOW;
		break;
	}

	use = true;
}


Enemy::~Enemy()
{
	polygon = NULL;
}

void Enemy::Update()
{
	this->transform.pos += ENEMY_SPEED;

	// 画面外判定
	Check();

	// 当たり判定
	if (bodyCollider->isHit)
	{
		use = false;
		GameSceneParticleManager::Instance()->SetEnemyExplosion(transform.pos);

		GameParameter::Instance()->AddCombo(1);
		GameParameter::Instance()->AddScore(ENEMY_POINT);

		PlaySE(SE_KICK);
	}
}

void Enemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ワールド変換行列の計算（Transform構造体に任せる）
	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//描画
	polygon->Draw();

	BoxCollider3D::DrawCollider(bodyCollider);
}

// 画面外判定
void Enemy::Check()
{
	if (transform.pos.x < -(SCREEN_WIDTH / 2)) {
		use = false;
	}
}