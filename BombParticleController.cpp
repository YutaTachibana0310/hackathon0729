//=====================================
//
//�e���v���[�g����[BombParticleController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BombParticleController.h"
#include "BombParticle.h"

/**************************************
�}�N����`
***************************************/
typedef BaseParticleController Base;

/**************************************
������
***************************************/
void BombParticleController::Init()
{
	//���_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(&D3DXVECTOR2(15.0f, 15.0f), &D3DXVECTOR2(8.0f, 8.0f));
	Base::LoadTexture("data/TEXTURE/bomb.png");

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(512);
	for (auto& particle : particleContainer)
	{
		particle = new BombParticle();
		static_cast<BombParticle*>(particle)->SetAnimParameter(&D3DXVECTOR2(8.0f, 8.0f));
	}

	//�G�~�b�^�R���e�i�쎌�G
	emitterContainer.resize(32);
	for (auto& emitter : emitterContainer)
	{
		emitter = new BombEmitter();
	}
}

/**************************************
���o
***************************************/
void BombParticleController::Emit()
{
	Base::ForEachEmitter(5, [](BaseEmitter* emitter, BaseParticle *particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}