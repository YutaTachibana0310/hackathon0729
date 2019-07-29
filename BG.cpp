//=====================================
//
//�w�i����[BG.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BG.h"
#include "Framework\ResourceManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�}�N����`
***************************************/
BG::BG()
{
	ResourceManager::Instance()->GetPolygon("GameBG", &polygon);
}

/**************************************

***************************************/
BG::~BG()
{
	polygon = NULL;
}

/**************************************
�}�N����`
***************************************/
void BG::Init()
{
	transform.pos = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
}

/**************************************
�}�N����`
***************************************/
void BG::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	polygon->Draw();
}
