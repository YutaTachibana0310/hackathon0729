//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[GameSceneParticleManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameSceneParticleManager.h"
#include "BombParticleController.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define GAMEPARTICLE_USE_DEBUG

#ifdef GAMEPARTICLE_USE_DEBUG
#include "debugWindow.h"
#endif

typedef SceneParticleManager Base;

/**************************************
�\���̒�`
***************************************/
enum ParticleController
{
	EnemyExplosion,
	ControllerMax
};

/**************************************
����������
***************************************/
void GameSceneParticleManager::Init()
{
	Base::Init();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�R���g���[���𐶐�
	controllers.resize(ControllerMax);
	controllers[EnemyExplosion] = new BombParticleController();

	//�e�p�[�e�B�N��������
	for (auto& controller : controllers)
	{
		controller->Init();
	}
}

/**************************************
�X�V����
***************************************/
void GameSceneParticleManager::Update(void)
{
#ifdef GAMEPARTICLE_USE_DEBUG
	DrawDebugWindow();
#endif

	Base::Update();
}

/**************************************
�G�t�F�N�g�Z�b�g����
***************************************/
void GameSceneParticleManager::SetEnemyExplosion(D3DXVECTOR3 pos)
{
	controllers[EnemyExplosion]->SetEmitter(&pos);
}

#ifdef GAMEPARTICLE_USE_DEBUG
/**************************************
�f�o�b�O�E�B���h�E
***************************************/
void GameSceneParticleManager::DrawDebugWindow(void)
{
	BeginDebugWindow("GameSceneParticle");

	if (DebugButton("Blood"))
	{
		SetEnemyExplosion(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	EndDebugWindow("GameSceneParticle");
}
#endif