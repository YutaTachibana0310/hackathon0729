//=====================================
//
//�^�C�g���V�[������[TitleScene.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TitleScene.h"
#include "Title.h"
#include "input.h"
#include "HexaTransition.h"
#include "Game.h"
#include "bgmManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void TitleScene::Init()
{
	HexaTransition::Instance()->SetTransition(false);
	InitTitle();

	PlayBGM(BGM_TITLE);
}

/**************************************
�I������
***************************************/
void TitleScene::Uninit()
{
	UninitTitle();
}

/**************************************
�X�V����
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
�`�揈��
***************************************/
void TitleScene::Draw()
{
	DrawTitle();
}
