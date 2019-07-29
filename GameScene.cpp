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

#include "Framework\ResourceManager.h"
#include "Player.h"
#include "BG.h"
#include "EnemyManager.h"

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
	ResourceManager::Instance()->MakePolygon("Sample", "data/TEXTURE/sample.png", PLAYER_POLYGON_SIZE);
	ResourceManager::Instance()->MakePolygon("GameBG", "data/TEXTURE/room.jpg", D3DXVECTOR2(200.0f, 100.0f));

	//インスタンス作成
	player = new Player();
	bg = new BG();

	//初期化処理
	player->Init();
	bg->Init();

	//インスタンス作成
	enemy = new EnemyManager();

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
}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	player->Update();
	enemy->Update();
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

	//レンダーステート復元
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
