//=====================================
//
//ゲームシーン処理[GameScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "debugWindow.h"
#include "HexaTransition.h"
#include "bgmManager.h"
#include "Framework\BoxCollider3D.h"
#include "Framework\ResourceManager.h"
#include "Player.h"
#include "BG.h"
#include "EnemyManager.h"
#include "BloodScreen.h"
#include "GameSceneParticleManager.h"
#include "Timer.h"
#include "Start.h"
#include "Finish.h"

/**************************************
マクロ定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	//リソース作成
	//第一引数でリソースを識別するタグ名、第二引数でテクスチャへのパス、第三引数でポリゴンサイズを指定
	ResourceManager::Instance()->MakePolygon("Player", "data/TEXTURE/charStand.png", PLAYER_POLYGON_SIZE);
	ResourceManager::Instance()->MakePolygon("Enemy", "data/TEXTURE/bug.png", ENEMY_POLYGON_SIZE);
	ResourceManager::Instance()->MakePolygon("GameBG", "data/TEXTURE/room.jpg", D3DXVECTOR2(200.0f, 100.0f));
	ResourceManager::Instance()->MakePolygon("PlayerUpper", "data/TEXTURE/charSomersault.png", PLAYER_POLYGON_SIZE);
	ResourceManager::Instance()->MakePolygon("PlayerMiddle", "data/TEXTURE/charMiddleKick.png", PLAYER_POLYGON_SIZE);
	ResourceManager::Instance()->MakePolygon("PlayerLower", "data/TEXTURE/charLowKick.png", PLAYER_POLYGON_SIZE);
	ResourceManager::Instance()->MakePolygon("PlayerDown", "data/TEXTURE/charDamage.png", PLAYER_POLYGON_SIZE);

	//インスタンス作成
	player = new Player();
	bg = new BG();

	//初期化処理
	player->Init();
	bg->Init();
	GameSceneParticleManager::Instance()->Init();

	//インスタンス作成
	enemy = new EnemyManager();

	//UI
	ui.push_back(new BloodScreen());
	start = new Start();


	//タイマー
	timer = new Timer();
	timer->Start();

	//トランジションアウト
	HexaTransition::Instance()->SetTransition(false);

	//BGMフェードイン
	FadeInBGM(BGM_BATTLESCENE, 60);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	//終了処理
	player->Uninit();

	//インスタンス削除
	SAFE_DELETE(player);
	SAFE_DELETE(bg);

	delete enemy;

	// UI削除
	for (auto &Object : ui)
	{
		SAFE_DELETE(Object);
	}
	ui.clear();
	ReleaseVector(ui);

	delete timer;
	delete start;
}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	if (start->Check() < START_TIME)
	{
		start->Update();
	}
	else
	{
		if (timer->Check() > 0)
		{
			player->Update();
			enemy->Update();

			GameSceneParticleManager::Instance()->Update();

			BoxCollider3D::UpdateCollision();
		}

		// タイマーチェック
		if (timer->Check() == 0)
		{
			if (timer->GetUse())
			{
				ui.push_back(new Finish());
				timer->Stop();
			}
		}

		for (auto & Object : ui)
		{
			Object->Update();
		}

		timer->Update();

	}
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//今回は2Dゲームなのでライティングをオフ、ポリゴンを裏面まで描画する
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//描画処理
	bg->Draw();
	player->Draw();
	enemy->Draw();

	GameSceneParticleManager::Instance()->Draw();

	timer->Draw();

	for (auto & Object : ui)
	{
		Object->Draw();
	}

	start->Draw();

	//レンダーステート復元
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}
