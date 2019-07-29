//=====================================
//
//テンプレートヘッダ[Template.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EXPLOSIONFLARE_H_
#define _EXPLOSIONFLARE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class ExplosionFlare : public AnimationParticle
{
public:
	void Init();
	void Update();

	D3DXVECTOR3 moveDir;
};

class ExplosionFlareEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif