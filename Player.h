//=====================================
//
//プレイヤーヘッダ[Player.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework\BoardPolygon.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	BoardPolygon* polygon;
	Transform transform;
};

#endif