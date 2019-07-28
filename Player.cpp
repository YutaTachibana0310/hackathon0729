//=====================================
//
//プレイヤー処理[Player.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Player.h"
#include "Framework\ResourceManager.h"
#include "input.h"

/**************************************
マクロ定義
***************************************/
#define PLAYER_MOVE_SPEED	(1.0f)

/**************************************
コンストラクタ
***************************************/
Player::Player()
{
	//ポリゴンをリソースマネージャから取得
	ResourceManager::Instance()->GetPolygon("Sample", &polygon);
}

/**************************************
デストラクタ
***************************************/
Player::~Player()
{
	//メモリの解放はリソースマネージャに任せるので参照をやめるだけ
	polygon = NULL;
}

/**************************************
初期化処理
***************************************/
void Player::Init()
{

}

/**************************************
終了処理
***************************************/
void Player::Uninit()
{

}

/**************************************
更新処理
***************************************/
void Player::Update()
{
	//移動方向
	D3DXVECTOR3 direction;
	ZeroMemory(&direction, sizeof(direction));

	//入力で移動方向を決定
	direction.x = GetHorizontalInputPress();
	direction.y = GetVerticalInputPress();

	//正規化して移動
	D3DXVec3Normalize(&direction, &direction);
	transform.pos += direction * PLAYER_MOVE_SPEED;
}

/**************************************
描画処理
***************************************/
void Player::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ワールド変換行列の計算（Transform構造体に任せる）
	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//描画
	polygon->Draw();
}
