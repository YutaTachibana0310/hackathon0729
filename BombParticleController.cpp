//=====================================
//
//テンプレート処理[BombParticleController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BombParticleController.h"
#include "BombParticle.h"

/**************************************
マクロ定義
***************************************/
typedef BaseParticleController Base;

/**************************************
初期化
***************************************/
void BombParticleController::Init()
{
	//頂点バッファ作成、テクスチャ読み込み
	Base::MakeUnitBuffer(&D3DXVECTOR2(15.0f, 15.0f), &D3DXVECTOR2(8.0f, 8.0f));
	Base::LoadTexture("data/TEXTURE/bomb.png");

	//パーティクルコンテナ作成
	particleContainer.resize(512);
	for (auto& particle : particleContainer)
	{
		particle = new BombParticle();
		static_cast<BombParticle*>(particle)->SetAnimParameter(&D3DXVECTOR2(8.0f, 8.0f));
	}

	//エミッタコンテナ作詞絵
	emitterContainer.resize(32);
	for (auto& emitter : emitterContainer)
	{
		emitter = new BombEmitter();
	}
}

/**************************************
放出
***************************************/
void BombParticleController::Emit()
{
	Base::ForEachEmitter(5, [](BaseEmitter* emitter, BaseParticle *particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}