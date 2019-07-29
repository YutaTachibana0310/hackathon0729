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


	//当たり判定生成
	bodyCollider = new BoxCollider3D(BoxCollider3DTag::Player, &transform.pos);
	bodyCollider->SetSize(PLAYTER_COLLIDER_SIZE);
	bodyCollider->active = true;

	attackCollider = new BoxCollider3D(BoxCollider3DTag::PlayerAttack, &attackPos);
	attackCollider->SetSize(PLAYER_ATTACKCOLLIDER_SIZE);
	attackCollider->active = false;
	
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
	transform.pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	
	isAttackNow = false;
	attackFrame = 0;
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

	//攻撃入力
	if (!isAttackNow)
	{
		//上段攻撃
		if (GetKeyboardTrigger(DIK_Z))
		{
			attackPos = ATTACK_UPPER_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
		}
		//中段攻撃
		else if (GetKeyboardTrigger(DIK_X))
		{
			attackPos = ATTACK_MIDDLE_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
		}
		//下段攻撃
		else if (GetKeyboardTrigger(DIK_C))
		{
			attackPos = ATTACK_LOWER_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
		}
	}

	//攻撃判定の更新
	if (isAttackNow)
	{
		attackFrame++;
		if (attackFrame == PLAYER_ATTACK_FRAME)
		{
			isAttackNow = false;
			attackCollider->active = false;
		}
	}
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

	//当たり判定描画
	BoxCollider3D::DrawCollider(bodyCollider);
	BoxCollider3D::DrawCollider(attackCollider);
}
