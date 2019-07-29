//=====================================
//
//�e���v���[�g����[BombParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BombParticle.h"

/**************************************
�}�N����`
***************************************/
#define BOMBPARTICLE_SPEED		(1.0f)

/**************************************
�p�[�e�B�N��������
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
�p�[�e�B�N���X�V
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
�G�~�b�^�[������
***************************************/
void BombEmitter::Init()
{
	duration = 5;
	cntFrame = 0;
	active = true;
}

/**************************************
�G�~�b�^�[�X�V
***************************************/
void BombEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}
}