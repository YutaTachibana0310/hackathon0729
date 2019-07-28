//=====================================
//
//�Q�[���V�[������[GameScene.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "debugWindow.h"
#include "HexaTransition.h"

#include "Framework\ResourceManager.h"
#include "Player.h"

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
	ResourceManager::Instance()->MakePolygon("Sample", "data/TEXTURE/sample.png", D3DXVECTOR2(20.0f, 20.0f));

	//�C���X�^���X�쐬
	player = new Player();

	//����������
	player->Init();

	//�g�����W�V�����A�E�g
	HexaTransition::Instance()->SetTransition(false);

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
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	player->Update();
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
	player->Draw();

	//�����_�[�X�e�[�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}