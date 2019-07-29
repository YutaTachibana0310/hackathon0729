//=====================================
//
//テンプレート処理[ExplosionFlare.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ExplosionFlare.h"

/**************************************
マクロ定義
***************************************/
#define BOMBPARTICLE_SPEED		(5.0f)

/**************************************
パーティクル初期化
***************************************/
void ExplosionFlare::Init()
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
void ExplosionFlare::Update()
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
void ExplosionFlareEmitter::Init()
{
	duration = 5;
	cntFrame = 0;
	active = true;
}

/**************************************
エミッター更新
***************************************/
void ExplosionFlareEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}
}