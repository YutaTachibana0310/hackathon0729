//=====================================
//
//�e���v���[�g����[ExplosionFlareController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ExplosionFlareController.h"
#include "ExplosionFlare.h"

/**************************************
�}�N����`
***************************************/
typedef BaseParticleController Base;

/**************************************
������
***************************************/
void ExplosionFlareController::Init()
{
	//���_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(&D3DXVECTOR2(5.0f, 5.0f), &D3DXVECTOR2(8.0f, 8.0f));
	Base::LoadTexture("data/TEXTURE/explosionFlare.png");

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(1024);
	for (auto& particle : particleContainer)
	{
		particle = new ExplosionFlare();
		static_cast<ExplosionFlare*>(particle)->SetAnimParameter(&D3DXVECTOR2(8.0f, 8.0f));
	}

	//�G�~�b�^�R���e�i�쎌�G
	emitterContainer.resize(32);
	for (auto& emitter : emitterContainer)
	{
		emitter = new ExplosionFlareEmitter();
	}
}

/**************************************
���o
***************************************/
void ExplosionFlareController::Emit()
{
	Base::ForEachEmitter(15, [](BaseEmitter* emitter, BaseParticle *particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}