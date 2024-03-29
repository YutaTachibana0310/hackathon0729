//=============================================================================
//
// ライト処理 [light.cpp]
// Author : GP12B332 21 立花雄太
//
//=============================================================================
#include "light.h"
#include "debugWindow.h"
#include <stdio.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LIGHT_SETTINGS_PATH		"data/SETTINGS/light.ini"	//設定ファイルのパス

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool SaveLightSettings(void);		//ライトの設定保存処理
bool LoadLightSettings(void);		//ライトの設定読み込み処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_aLight[NUM_LIGHT];		// ライトのワーク

D3DXCOLOR lightDiffuse[NUM_LIGHT];

//=============================================================================
// ライトの初期化処理
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	bool loadSuccess = LoadLightSettings();

	if (!loadSuccess)
	{
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&g_aLight[2], sizeof(D3DLIGHT9));
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

		// ライト0の設定
		g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLight[0].Ambient = D3DXCOLOR(0.1f, 0.1f, 0.5f, 1.0f);
		vecDir = D3DXVECTOR3(0.80f, -1.0f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

		// ライト1の設定
		g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		g_aLight[1].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		g_aLight[1].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		vecDir = D3DXVECTOR3(-0.0f, 1.00f, -0.50f);
		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

		// ライト2の設定
		g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		g_aLight[2].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		g_aLight[2].Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		vecDir = D3DXVECTOR3(-0.40f, -0.5f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[2].Direction, &vecDir);
	}

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(0, &g_aLight[0]);
	pDevice->LightEnable(0, TRUE);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(1, &g_aLight[1]);
	pDevice->LightEnable(1, TRUE);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(2, &g_aLight[2]);
	pDevice->LightEnable(2, TRUE);

	// ライティングモード
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{

}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{

}

//=============================================================================
// ライト情報取得処理
//=============================================================================
void GetLightData(D3DCOLORVALUE diffuse[], D3DCOLORVALUE ambient[], D3DXVECTOR4 dir[])
{
	for (int i = 0; i < NUM_LIGHT; i++)
	{
		diffuse[i] = g_aLight[i].Diffuse;
		ambient[i] = g_aLight[i].Ambient;
		dir[i] = D3DXVECTOR4(g_aLight[i].Direction, 1.0f);
	}
}

//=============================================================================
// ライトの設定読み込み処理
//=============================================================================
bool LoadLightSettings(void)
{
	FILE *fp = fopen(LIGHT_SETTINGS_PATH, "rb");

	if (fp == NULL)
		return false;

	fread(g_aLight, sizeof(D3DLIGHT9), NUM_LIGHT, fp);

	fclose(fp);
	return true;
}

//=============================================================================
// ライトの設定保存処理
//=============================================================================
bool SaveLightSettings(void)
{
	FILE *fp = fopen(LIGHT_SETTINGS_PATH, "wb");

	if (fp == NULL)
		return false;

	fwrite(g_aLight, sizeof(D3DLIGHT9), NUM_LIGHT, fp);
	fclose(fp);
	return true;
}