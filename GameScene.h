//=====================================
//
//ゲームシーンヘッダ[GameScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "main.h"
#include "Framework\IStateScene.h"

#include "Framework\BoxCollider3D.h"

/**************************************
マクロ定義
***************************************/
// 出現場所
#define START_HIGH		D3DXVECTOR3(200.0f, 40.0f, 0.0f)
#define START_MIDDLE	D3DXVECTOR3(200.0f, 0.0f, 0.0f)
#define START_LOW		D3DXVECTOR3(200.0f, -40.0f, 0.0f)

/**************************************
前方宣言
***************************************/
class Player;
class BG;
class EnemyManager;

/**************************************
クラス定義
***************************************/
class GameScene : public IStateScene
{
public:
	void Init() override;
	void Uninit() override;
	void Update(HWND hWnd) override;
	void Draw() override;

private:
	Player *player;
	BG *bg;
	EnemyManager *enemy;
};

#endif