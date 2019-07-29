//=====================================
//
//ゲームパラメータヘッダ[GameParameter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEPARAMETER_H_
#define _GAMEPARAMETER_H_

#include "main.h"
#include "Framework\BaseSingleton.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class GameParameter : public BaseSingleton<GameParameter>
{
	friend class BaseSingleton<GameParameter>;

public:
	void Init();

	void AddCombo(int num);
	void AddScore(int point);

	int score;
	int combo;
};

#endif