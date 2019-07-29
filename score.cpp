//*****************************************************************************
// スコア処理[score.cpp]
// Author: GA12A 染矢　晃介
//*****************************************************************************
#include "main.h"
#include "score.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureScore = NULL;					// スコアテクスチャへのポリゴン
LPDIRECT3DTEXTURE9		D3DTextureScoreRogo = NULL;				// スコアロゴテクスチャへのポリゴン

VERTEX_2D				VertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// スコアの頂点情報格納ワーク
VERTEX_2D				VertexWkScoreRogo[NUM_VERTEX];			// スコアの頂点情報格納ワーク

D3DXVECTOR3				PosScore;								// スコアの位置
D3DXVECTOR3				PosScoreRogo;							// スコアロゴの位置

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_SCORE,				// ファイルの名前
			&D3DTextureScore);				// 読み込むメモリのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_GAME_ROGO,				// ファイルの名前
		&D3DTextureScoreRogo);				// 読み込むメモリのポインタ

	PosScore = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);
	PosScoreRogo = D3DXVECTOR3((float)SCORE_ROGO_POS_X, (float)SCORE_ROGO_POS_Y, 0.0f);
	// 頂点情報の作成
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if (D3DTextureScore != NULL)
	{	// テクスチャの開放
		D3DTextureScore->Release();
		D3DTextureScore = NULL;
	}

	if (D3DTextureScoreRogo != NULL)
	{	// テクスチャの開放
		D3DTextureScoreRogo->Release();
		D3DTextureScoreRogo = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	SetScore(1000); //お試し
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureScore);

	// スコア
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkScore[i], sizeof(VERTEX_2D));
	}

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureScoreRogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkScoreRogo, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(void)
{
	
	// 桁数分処理する
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点座標の設定
		VertexWkScore[i][0].vtx.x = -SCORE_WIDE * i + PosScore.x;
		VertexWkScore[i][0].vtx.y = PosScore.y;
		VertexWkScore[i][0].vtx.z = 0.0f;
		VertexWkScore[i][1].vtx.x = -SCORE_WIDE * i + PosScore.x + TEXTURE_SCORE_SIZE_X;
		VertexWkScore[i][1].vtx.y = PosScore.y;
		VertexWkScore[i][1].vtx.z = 0.0f;
		VertexWkScore[i][2].vtx.x = -SCORE_WIDE * i + PosScore.x;
		VertexWkScore[i][2].vtx.y = PosScore.y + TEXTURE_SCORE_SIZE_Y;
		VertexWkScore[i][2].vtx.z = 0.0f;
		VertexWkScore[i][3].vtx.x = -SCORE_WIDE * i + PosScore.x + TEXTURE_SCORE_SIZE_X;
		VertexWkScore[i][3].vtx.y = PosScore.y + TEXTURE_SCORE_SIZE_Y;
		VertexWkScore[i][3].vtx.z = 0.0f;

		// rhwの設定
		VertexWkScore[i][0].rhw =
		VertexWkScore[i][1].rhw =
		VertexWkScore[i][2].rhw =
		VertexWkScore[i][3].rhw = 1.0f;

		// 反射光の設定
		VertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		VertexWkScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		VertexWkScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		VertexWkScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		VertexWkScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//ロゴの頂点座標の設定
	VertexWkScoreRogo[0].vtx = D3DXVECTOR3(SCORE_ROGO_POS_X, SCORE_ROGO_POS_Y, 0);
	VertexWkScoreRogo[1].vtx = D3DXVECTOR3(SCORE_ROGO_POS_X + TEXTURE_SCORE_ROGO_SIZE_X, SCORE_ROGO_POS_Y, 0);
	VertexWkScoreRogo[2].vtx = D3DXVECTOR3(SCORE_ROGO_POS_X, SCORE_ROGO_POS_Y + TEXTURE_SCORE_ROGO_SIZE_Y, 0);
	VertexWkScoreRogo[3].vtx = D3DXVECTOR3(SCORE_ROGO_POS_X + TEXTURE_SCORE_ROGO_SIZE_X, SCORE_ROGO_POS_Y + TEXTURE_SCORE_ROGO_SIZE_Y, 0);

	// rhwの設定
	VertexWkScoreRogo[0].rhw =
	VertexWkScoreRogo[1].rhw =
	VertexWkScoreRogo[2].rhw =
	VertexWkScoreRogo[3].rhw = 1.0f;

	// 反射光の設定
	VertexWkScoreRogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkScoreRogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkScoreRogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkScoreRogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	VertexWkScoreRogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	VertexWkScoreRogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	VertexWkScoreRogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	VertexWkScoreRogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// スコアをセットする
// 引数:num :描画する点数。
//=============================================================================
void SetScore(int num)
{

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(num % 10);
		VertexWkScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		VertexWkScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		VertexWkScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		VertexWkScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		num /= 10;
	}

}