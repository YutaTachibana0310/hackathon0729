//=====================================
//
//�Q�[���V�[���w�b�_[GameScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "main.h"
#include "Framework\IStateScene.h"

#include "Framework\BoxCollider3D.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�O���錾
***************************************/
class Player;

/**************************************
�N���X��`
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
};

#endif