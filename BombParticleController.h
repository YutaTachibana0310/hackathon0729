//=====================================
//
//ボムパーティクルコントローラヘッダ[BombParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOMBPARTICLECONTROLLER_H_
#define _BOMBPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BombParticleController : public BaseParticleController
{
	void Init();
	void Emit();
};

#endif