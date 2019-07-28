//=====================================
//
//ヘキサトランジションヘッダ[HexaTransition.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _HEXATRANSITION_H_
#define _HEXATRANSITION_H_

#include "main.h"
#include "Framework\BaseTransition.h"
#include "Framework\Easing.h"
#include "Framework\BaseSingleton.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class HexaTransition : public BaseTransition, public BaseSingleton<HexaTransition>
{
	friend class BaseSingleton<HexaTransition>;

public:
	HexaTransition()
	{
		cntFrame = 120;
	}

	void Update();

	void SetTransition(bool isStart, std::function<void(void)> func = NULL);

private:
	int cntFrame;
	D3DXVECTOR3 initScale;
	D3DXVECTOR3 goalScale;
	EasingType easeType;
};

#endif