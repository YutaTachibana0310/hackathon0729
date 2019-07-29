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
// �o���ꏊ
#define START_HIGH		D3DXVECTOR3(200.0f, 40.0f, 0.0f)
#define START_MIDDLE	D3DXVECTOR3(200.0f, 0.0f, 0.0f)
#define START_LOW		D3DXVECTOR3(200.0f, -40.0f, 0.0f)

/**************************************
�O���錾
***************************************/
class Player;
class BG;
class EnemyManager;

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
	BG *bg;
	EnemyManager *enemy;
};

#endif