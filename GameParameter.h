//=====================================
//
//�Q�[���p�����[�^�w�b�_[GameParameter.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEPARAMETER_H_
#define _GAMEPARAMETER_H_

#include "main.h"
#include "Framework\BaseSingleton.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class GameParameter : public BaseSingleton<GameParameter>
{
	friend class BaseSingleton<GameParameter>;

public:
	void Init();

	void AddCombo(int num);
	void AddScore(int point);

	int score;
	int combo;
};

#endif