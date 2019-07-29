//=====================================
//
//テンプレートヘッダ[Template.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENEPARTICLEMANAGER_H_
#define _GAMESCENEPARTICLEMANAGER_H_

#include "main.h"
#include "Framework\SceneParticleManager.h"
#include "Framework\BaseSingleton.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
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