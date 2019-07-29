//=====================================
//
//�e���v���[�g�w�b�_[Template.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCENEPARTICLEMANAGER_H_
#define _GAMESCENEPARTICLEMANAGER_H_

#include "main.h"
#include "Framework\SceneParticleManager.h"
#include "Framework\BaseSingleton.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class GameSceneParticleManager : public SceneParticleManager, public BaseSingleton<GameSceneParticleManager>
{
	friend class BaseSingleton<GameSceneParticleManager>;
public:
	void Init();
	void Update();

	void SetEnemyExplosion(D3DXVECTOR3 pos);

	void DrawDebugWindow();
};

#endif