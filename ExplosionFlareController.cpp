//=====================================
//
//テンプレート処理[ExplosionFlareController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ExplosionFlareController.h"
#include "ExplosionFlare.h"

/**************************************
マクロ定義
***************************************/
typedef BaseParticleController Base;

/**************************************
初期化
***************************************/
void ExplosionFlareController::Init()
{
	//頂点バッファ作成、テクスチャ読み込み
	Base::MakeUnitBuffer(&D3DXVECTOR2(5.0f, 5.0f), &D3DXVECTOR2(8.0f, 8.0f));
	Base::LoadTexture("data/TEXTURE/explosionFlare.png");

	//パーティクルコンテナ作成
	particleContainer.resize(1024);
	for (auto& particle : particleContainer)
	{
		particle = new ExplosionFlare();
		static_cast<ExplosionFlare*>(particle)->SetAnimParameter(&D3DXVECTOR2(8.0f, 8.0f));
	}

	//エミッタコンテナ作詞絵
	emitterContainer.resize(32);
	for (auto& emitter : emitterContainer)
	{
		emitter = new ExplosionFlareEmitter();
	}
}

/**************************************
放出
***************************************/
void ExplosionFlareController::Emit()
{
	Base::ForEachEmitter(15, [](BaseEmitter* emitter, BaseParticle *particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}