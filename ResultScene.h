//=====================================
//
//���U���g�V�[���w�b�_[ResultScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_

#include "main.h"
#include "Framework\IStateScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class ResultScene : public IStateScene
{
public:
	void Init() override;
	void Uninit() override;
	void Update(HWND hWnd) override;
	void Draw() override;
};

#endif