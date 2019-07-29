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
	polygonContainer.resize(PlayerTextureMax);
	//ポリゴンをリソースマネージャから取得
	ResourceManager::Instance()->GetPolygon("Player", &polygonContainer[PlayerStand]);
	ResourceManager::Instance()->GetPolygon("PlayerUpper", &polygonContainer[PlayerUpper]);
	ResourceManager::Instance()->GetPolygon("PlayerMiddle", &polygonContainer[PlayerMiddle]);
	ResourceManager::Instance()->GetPolygon("PlayerLower", &polygonContainer[PlayerLower]);
	ResourceManager::Instance()->GetPolygon("PlayerDown", &polygonContainer[PlayerDown]);

	//当たり判定生成
	bodyCollider = new BoxCollider3D(BoxCollider3DTag::Player, &transform.pos);
	bodyCollider->SetSize(PLAYTER_COLLIDER_SIZE);
	bodyCollider->active = true;

	attackCollider = new BoxCollider3D(BoxCollider3DTag::PlayerAttack, &attackPos);
	attackCollider->SetSize(PLAYER_ATTACKCOLLIDER_SIZE);
	attackCollider->active = false;


	isAttackNow = false;
	attackFrame = 0;

	isInvincible = false;
	invincibleFrame = 0;

	isDownNow = false;
	downFrame = 0;
}

/**************************************
デストラクタ
***************************************/
Player::~Player()
{
	//メモリの解放はリソースマネージャに任せるので参照をやめるだけ
	for (auto& polygon : polygonContainer)
	{
		polygon = NULL;
	}
}

/**************************************
初期化処理
***************************************/
void Player::Init()
{
	transform.pos = PLAYER_INIT_POS;

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
	if (!isAttackNow && !isDownNow)
	{
		//上段攻撃
		if (GetKeyboardTrigger(DIK_Z))
		{
			attackPos = ATTACK_UPPER_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
			textureID = PlayerUpper;
		}
		//中段攻撃
		else if (GetKeyboardTrigger(DIK_X))
		{
			attackPos = ATTACK_MIDDLE_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
			textureID = PlayerMiddle;
		}
		//下段攻撃
		else if (GetKeyboardTrigger(DIK_C))
		{
			attackPos = ATTACK_LOWER_POS;
			isAttackNow = true;
			attackFrame = 0;
			attackCollider->active = true;
			textureID = PlayerLower;
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
			textureID = PlayerStand;
		}
	}

	//無敵時間の更新
	if (isInvincible && !isDownNow)
	{
		invincibleFrame++;
		if (invincibleFrame == PLAYER_INVINCBILE_FRAME)
		{
			isInvincible = false;
			bodyCollider->active = true;
		}
	}

	//行動不能時間の更新
	if (isDownNow)
	{
		downFrame++;
		if (downFrame == PLAYER_DONW_FRAME)
		{
			isDownNow = false;
			textureID = PlayerStand;
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
	polygonContainer[textureID]->Draw();

	//当たり判定描画
	BoxCollider3D::DrawCollider(bodyCollider);
	BoxCollider3D::DrawCollider(attackCollider);
}

/**************************************
エネミーとの衝突処理
***************************************/
void Player::OnHitEnemy()
{
	downFrame = 0;
	isDownNow = true;

	isInvincible = true;
	invincibleFrame = 0;

	textureID = PlayerDown;
}