//=====================================
//
//�v���C���[�w�b�_[Player.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework\BoardPolygon.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	BoardPolygon* polygon;
	Transform transform;
};

#endif