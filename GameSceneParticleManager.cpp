//=====================================
//
//ゲームパーティクルマネージャ処理[GameSceneParticleManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameSceneParticleManager.h"
#include "BombParticleController.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define GAMEPARTICLE_USE_DEBUG

#ifdef GAMEPARTICLE_USE_DEBUG
#include "debugWindow.h"
#endif

typedef SceneParticleManager Base;

/**************************************
構造体定義
***************************************/
enum ParticleController
{
	EnemyExplosion,
	ControllerMax
};

/**************************************
初期化処理
***************************************/
void GameSceneParticleManager::Init()
{
	Base::Init();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各コントローラを生成
	controllers.resize(ControllerMax);
	controllers[EnemyExplosion] = new BombParticleController();

	//各パーティクル初期化
	for (auto& controller : controllers)
	{
		controller->Init();
	}
}

/**************************************
更新処理
***************************************/
void GameSceneParticleManager::Update(void)
{
#ifdef GAMEPARTICLE_USE_DEBUG
	DrawDebugWindow();
#endif

	Base::Update();
}

/**************************************
エフェクトセット処理
***************************************/
void GameSceneParticleManager::SetEnemyExplosion(D3DXVECTOR3 pos)
{
	controllers[EnemyExplosion]->SetEmitter(&pos);
}

#ifdef GAMEPARTICLE_USE_DEBUG
/**************************************
デバッグウィンドウ
***************************************/
void GameSceneParticleManager::DrawDebugWindow(void)
{
	BeginDebugWindow("GameSceneParticle");

	if (DebugButton("Blood"))
	{
		SetEnemyExplosion(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	EndDebugWindow("GameSceneParticle");
}
#endif