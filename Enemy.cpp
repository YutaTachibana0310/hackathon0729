#include "main.h"
#include "Enemy.h"
#include "Framework\ResourceManager.h"
#include "GameScene.h"

#define ENEMY_SPEED	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)

Enemy::Enemy(int num)
{
	//ポリゴンをリソースマネージャから取得
	ResourceManager::Instance()->GetPolygon("Sample", &polygon);

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
	//this->transform.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
}

// 画面外判定
void Enemy::Check()
{
	if (transform.pos.x < -(SCREEN_WIDTH / 2)) {
		use = false;
	}
}