//=====================================
//
//�e���v���[�g�w�b�_[Template.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EXPLOSIONFLARE_H_
#define _EXPLOSIONFLARE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
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