//=====================================
//
//�`���[�g���A���V�[���w�b�_[TutorialScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALSCENE_H_
#define _TUTORIALSCENE_H_

#include "main.h"
#include "Framework\IStateScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class TutorialScene : public IStateScene
{
public:
	void Init() override;
	void Uninit() override;
	void Update(HWND hWnd) override;
	void Draw() override;
};

#endif