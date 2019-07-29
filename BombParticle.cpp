//=====================================
//
//テンプレート処理[BombParticle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BombParticle.h"

/**************************************
マクロ定義
***************************************/
#define BOMBPARTICLE_SPEED		(1.0f)

/**************************************
パーティクル初期化
***************************************/
void BombParticle::Init()
{
	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = RandomRangef(-1.0f, 1.0f);
	D3DXVec3Normalize(&moveDir, &moveDir);

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));

	cntFrame = 0;
	lifeFrame = RandomRange(10, 20);
	active = true;
}

/**************************************
パーティクル更新
***************************************/
void BombParticle::Update()
{
	cntFrame++;

	transform.pos += moveDir * BOMBPARTICLE_SPEED;

	float t = 1.f * cntFrame / lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
エミッター初期化
***************************************/
void BombEmitter::Init()
{
	duration = 5;
	cntFrame = 0;
	active = true;
}

/**************************************
エミッター更新
***************************************/
void BombEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}
}