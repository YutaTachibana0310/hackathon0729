//=====================================
//
//タイトルシーン処理[TitleScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TitleScene.h"
#include "Title.h"
#include "input.h"
#include "HexaTransition.h"
#include "Game.h"
#include "bgmManager.h"

/**************************************
マクロ定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void TitleScene::Init()
{
	HexaTransition::Instance()->SetTransition(false);
	InitTitle();

	PlayBGM(BGM_TITLE);
}

/**************************************
終了処理
***************************************/
void TitleScene::Uninit()
{
	UninitTitle();
}

/**************************************
更新処理
***************************************/
void TitleScene::Update(HWND hWnd)
{
	UpdateTitle();

	if (GetKeyboardTrigger(DIK_Z) || GetKeyboardTrigger(DIK_X) || GetKeyboardTrigger(DIK_C))
	{
		FadeOutBGM(BGM_TITLE, 30);
		HexaTransition::Instance()->SetTransition(true, []() 
		{
			ChangeScene(SceneGame); 
		});
	}
}

/**************************************
描画処理
***************************************/
void TitleScene::Draw()
{
	DrawTitle();
}
