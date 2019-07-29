//*****************************************************************************
// コンボ処理[combo.cpp]
// Author:染矢　晃介
//*****************************************************************************
#include "main.h"
#include "combo.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCombo(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureCombo = NULL;					// コンボテクスチャへのポリゴン
LPDIRECT3DTEXTURE9		D3DTextureComboRogo = NULL;				// ロゴテクスチャへのポリゴン
VERTEX_2D				VertexWkCombo[COMBO_DIGIT][NUM_VERTEX];	// コンボ頂点情報格納ワーク
VERTEX_2D				VertexWkComboRogo[NUM_VERTEX];			// ロゴ頂点情報格納ワーク
D3DXVECTOR3				PosCombo;								// コンボの位置
D3DXVECTOR3				PosComboRogo;							// コンボロゴの位置

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCombo()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_COMBO,				// ファイルの名前
			&D3DTextureCombo);				// 読み込むメモリのポインタ
	
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_GAME_COMBO_ROGO,				// ファイルの名前
		&D3DTextureComboRogo);				// 読み込むメモリのポインタ

	PosCombo = D3DXVECTOR3((float)COMBO_POS_X, (float)COMBO_POS_Y, 0.0f);
	PosComboRogo = D3DXVECTOR3((float)COMBO_ROGO_POS_X, (float)COMBO_ROGO_POS_Y, 0.0f);

	// 頂点情報の作成
	MakeVertexCombo();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCombo(void)
{
	if (D3DTextureCombo != NULL)
	{	// テクスチャの開放
		D3DTextureCombo->Release();
		D3DTextureCombo = NULL;
	}

	if (D3DTextureComboRogo != NULL)
	{	// テクスチャの開放
		D3DTextureComboRogo->Release();
		D3DTextureComboRogo = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCombo(void)
{
	SetCombo(1); //お試し
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureCombo);

	// スコア
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkCombo[i], sizeof(VERTEX_2D));
	}

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureComboRogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkComboRogo, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexCombo(void)
{

	// 桁数分処理する
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// 頂点座標の設定
		VertexWkCombo[i][0].vtx.x = -COMBO_WIDE * i + PosCombo.x;
		VertexWkCombo[i][0].vtx.y = PosCombo.y;
		VertexWkCombo[i][0].vtx.z = 0.0f;
		VertexWkCombo[i][1].vtx.x = -COMBO_WIDE * i + PosCombo.x + TEXTURE_COMBO_SIZE_X;
		VertexWkCombo[i][1].vtx.y = PosCombo.y;
		VertexWkCombo[i][1].vtx.z = 0.0f;
		VertexWkCombo[i][2].vtx.x = -COMBO_WIDE * i + PosCombo.x;
		VertexWkCombo[i][2].vtx.y = PosCombo.y + TEXTURE_COMBO_SIZE_Y;
		VertexWkCombo[i][2].vtx.z = 0.0f;
		VertexWkCombo[i][3].vtx.x = -COMBO_WIDE * i + PosCombo.x + TEXTURE_COMBO_SIZE_X;
		VertexWkCombo[i][3].vtx.y = PosCombo.y + TEXTURE_COMBO_SIZE_Y;
		VertexWkCombo[i][3].vtx.z = 0.0f;

		// rhwの設定
		VertexWkCombo[i][0].rhw =
		VertexWkCombo[i][1].rhw =
		VertexWkCombo[i][2].rhw =
		VertexWkCombo[i][3].rhw = 1.0f;

		// 反射光の設定
		VertexWkCombo[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkCombo[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkCombo[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkCombo[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		VertexWkCombo[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		VertexWkCombo[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		VertexWkCombo[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		VertexWkCombo[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//ロゴの頂点座標の設定
	VertexWkComboRogo[0].vtx = D3DXVECTOR3(COMBO_ROGO_POS_X, COMBO_ROGO_POS_Y, 0);
	VertexWkComboRogo[1].vtx = D3DXVECTOR3(COMBO_ROGO_POS_X + TEXTURE_COMBO_ROGO_SIZE_X, COMBO_ROGO_POS_Y, 0);
	VertexWkComboRogo[2].vtx = D3DXVECTOR3(COMBO_ROGO_POS_X, COMBO_ROGO_POS_Y + TEXTURE_COMBO_ROGO_SIZE_Y, 0);
	VertexWkComboRogo[3].vtx = D3DXVECTOR3(COMBO_ROGO_POS_X + TEXTURE_COMBO_ROGO_SIZE_X, COMBO_ROGO_POS_Y + TEXTURE_COMBO_ROGO_SIZE_Y, 0);

	// rhwの設定
	VertexWkComboRogo[0].rhw =
	VertexWkComboRogo[1].rhw =
	VertexWkComboRogo[2].rhw =
	VertexWkComboRogo[3].rhw = 1.0f;

	// 反射光の設定
	VertexWkComboRogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkComboRogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkComboRogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkComboRogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	VertexWkComboRogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	VertexWkComboRogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	VertexWkComboRogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	VertexWkComboRogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// スコアをセットする
// 引数:num :描画する点数。
//=============================================================================
void SetCombo(int num)
{

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(num % 10);
		VertexWkCombo[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		VertexWkCombo[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		VertexWkCombo[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		VertexWkCombo[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		num /= 10;
	}

}