//=====================================
//
//�Q�[���V�[������[GameScene.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "debugWindow.h"
#include "HexaTransition.h"
#include "bgmManager.h"

#include "Framework\ResourceManager.h"
#include "Player.h"
#include "BG.h"
#include "EnemyManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void GameScene::Init()
{
	//���\�[�X�쐬
	//�������Ń��\�[�X�����ʂ���^�O���A�������Ńe�N�X�`���ւ̃p�X�A��O�����Ń|���S���T�C�Y���w��
	ResourceManager::Instance()->MakePolygon("Sample", "data/TEXTURE/sample.png", PLAYER_POLYGON_SIZE);
	ResourceManager::Instance()->MakePolygon("GameBG", "data/TEXTURE/room.jpg", D3DXVECTOR2(200.0f, 100.0f));

	//�C���X�^���X�쐬
	player = new Player();
	bg = new BG();

	//����������
	player->Init();
	bg->Init();

	//�C���X�^���X�쐬
	enemy = new EnemyManager();

	//�g�����W�V�����A�E�g
	HexaTransition::Instance()->SetTransition(false);

	//BGM�t�F�[�h�C��
	FadeInBGM(BGM_BATTLESCENE, 60);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	//�I������
	player->Uninit();

	//�C���X�^���X�폜
	SAFE_DELETE(player);
	SAFE_DELETE(bg);

	delete enemy;
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	player->Update();
	enemy->Update();
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����2D�Q�[���Ȃ̂Ń��C�e�B���O���I�t�A�|���S���𗠖ʂ܂ŕ`�悷��
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�`�揈��
	bg->Draw();
	player->Draw();
	enemy->Draw();

	//�����_�[�X�e�[�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
