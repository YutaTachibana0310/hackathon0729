//=====================================
//
//リザルトシーン処理[ResultScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ResultScene.h"
#include "Result.h"
#include "Game.h"
#include "input.h"
#include "HexaTransition.h"
#include "bgmManager.h"
#include "resultscore.h"
#include "GameParameter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void ResultScene::Init()
{
	HexaTransition::Instance()->SetTransition(false);
	InitResult();
	InitResultScore();

	PlayBGM(BGM_RESULT);
}

/**************************************
終了処理
***************************************/
void ResultScene::Uninit()
{
	UninitResult();
	UninitResultScore();
}

/**************************************
更新処理
***************************************/
void ResultScene::Update(HWND hWnd)
{
	UpdateResult();
	UpdateResultScore();

	if (GetKeyboardTrigger(DIK_Z) || GetKeyboardTrigger(DIK_X) || GetKeyboardTrigger(DIK_C))
	{
		FadeOutBGM(BGM_RESULT, 30);
		HexaTransition::Instance()->SetTransition(true, []()
		{
			ChangeScene(SceneTitle);
		});
	}
}

/**************************************
描画処理
***************************************/
void ResultScene::Draw()
{
	DrawResult();

	SetResultScore(GameParameter::Instance()->score);
	DrawResultScore();
}
