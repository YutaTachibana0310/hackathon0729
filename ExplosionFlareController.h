//=====================================
//
//ボムパーティクルコントローラヘッダ[ExplosionFlareController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EXPLOSIONFLARECONTROLLER_H_
#define _EXPLOSIONFLARECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class ExplosionFlareController : public BaseParticleController
{
	void Init();
	void Emit();
};

#endif