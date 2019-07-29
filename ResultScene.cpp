//=====================================
//
//���U���g�V�[������[ResultScene.cpp]
//Author:GP12A332 21 ���ԗY��
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
�}�N����`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void ResultScene::Init()
{
	HexaTransition::Instance()->SetTransition(false);
	InitResult();
	InitResultScore();

	PlayBGM(BGM_RESULT);
}

/**************************************
�I������
***************************************/
void ResultScene::Uninit()
{
	UninitResult();
	UninitResultScore();
}

/**************************************
�X�V����
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
�`�揈��
***************************************/
void ResultScene::Draw()
{
	DrawResult();

	SetResultScore(GameParameter::Instance()->score);
	DrawResultScore();
}
