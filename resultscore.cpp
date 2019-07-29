//*****************************************************************************
// スコア処理[score.cpp]
// Author: 染矢　晃介
//*****************************************************************************
#include "main.h"
#include "resultscore.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResultScore(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureResultScore = NULL;							// スコアテクスチャへのポリゴン
VERTEX_2D				VertexWkResultScore[RESULT_SCORE_DIGIT][NUM_VERTEX];	// スコアの頂点情報格納ワーク
D3DXVECTOR3				PosResultScore;										// スコアの位置

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResultScore()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_GAME_RESULT_SCORE,				// ファイルの名前
		&D3DTextureResultScore);				// 読み込むメモリのポインタ

										// テクスチャの読み込み
	

	PosResultScore = D3DXVECTOR3((float)RESULT_SCORE_POS_X, (float)RESULT_SCORE_POS_Y, 0.0f);
	
	// 頂点情報の作成
	MakeVertexResultScore();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultScore(void)
{
	if (D3DTextureResultScore != NULL)
	{	// テクスチャの開放
		D3DTextureResultScore->Release();
		D3DTextureResultScore = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultScore(void)
{
	SetResultScore(1000); //お試し
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureResultScore);

	// スコア
	for (int i = 0; i < RESULT_SCORE_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkResultScore[i], sizeof(VERTEX_2D));
	}

	
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResultScore(void)
{

	// 桁数分処理する
	for (int i = 0; i < RESULT_SCORE_DIGIT; i++)
	{
		// 頂点座標の設定
		VertexWkResultScore[i][0].vtx.x = -RESULT_SCORE_WIDE * i + PosResultScore.x;
		VertexWkResultScore[i][0].vtx.y = PosResultScore.y;
		VertexWkResultScore[i][0].vtx.z = 0.0f;
		VertexWkResultScore[i][1].vtx.x = -RESULT_SCORE_WIDE * i + PosResultScore.x + TEXTURE_RESULT_SCORE_SIZE_X;
		VertexWkResultScore[i][1].vtx.y = PosResultScore.y;
		VertexWkResultScore[i][1].vtx.z = 0.0f;
		VertexWkResultScore[i][2].vtx.x = -RESULT_SCORE_WIDE * i + PosResultScore.x;
		VertexWkResultScore[i][2].vtx.y = PosResultScore.y + TEXTURE_RESULT_SCORE_SIZE_Y;
		VertexWkResultScore[i][2].vtx.z = 0.0f;
		VertexWkResultScore[i][3].vtx.x = -RESULT_SCORE_WIDE * i + PosResultScore.x + TEXTURE_RESULT_SCORE_SIZE_X;
		VertexWkResultScore[i][3].vtx.y = PosResultScore.y + TEXTURE_RESULT_SCORE_SIZE_Y;
		VertexWkResultScore[i][3].vtx.z = 0.0f;

		// rhwの設定
		VertexWkResultScore[i][0].rhw =
		VertexWkResultScore[i][1].rhw =
		VertexWkResultScore[i][2].rhw =
		VertexWkResultScore[i][3].rhw = 1.0f;

		// 反射光の設定
		VertexWkResultScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkResultScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkResultScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkResultScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		VertexWkResultScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		VertexWkResultScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		VertexWkResultScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		VertexWkResultScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	
	return S_OK;
}

//=============================================================================
// スコアをセットする
// 引数:num :描画する点数。
//=============================================================================
void SetResultScore(int num)
{

	for (int i = 0; i < RESULT_SCORE_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(num % 10);
		VertexWkResultScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		VertexWkResultScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		VertexWkResultScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		VertexWkResultScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		num /= 10;
	}

}