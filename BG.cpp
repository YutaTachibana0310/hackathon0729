//=====================================
//
//背景処理[BG.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BG.h"
#include "Framework\ResourceManager.h"

/**************************************
マクロ定義
***************************************/

/**************************************
マクロ定義
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
マクロ定義
***************************************/
void BG::Init()
{
	transform.pos = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
}

/**************************************
マクロ定義
***************************************/
void BG::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	polygon->Draw();
}
