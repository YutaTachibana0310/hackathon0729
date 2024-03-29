//=====================================
//
//ゲームパラメータ処理[GameParameter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameParameter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
初期化
***************************************/
void GameParameter::Init()
{
	score = 0;
	combo = 0;
}

/**************************************
コンボ加算
***************************************/
void GameParameter::AddCombo(int num)
{
	combo += num;
}

void GameParameter::ResetCombo()
{
	combo = 0;
}

/**************************************
スコア加算
***************************************/
void GameParameter::AddScore(int point)
{
	score += (int)(point * (1.0f + combo * 0.1f));
}