//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 名和 遼汰朗
//
//=============================================================================
#include "Result.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RESULT		("data/TEXTURE/result001.png")			// 読み込むテクスチャファイル名
#define	RESULT_POS_X			(0)									// タイトルの表示位置
#define	RESULT_POS_Y			(0)									// タイトルの表示位置
#define	RESULT_SIZE_X			(SCREEN_WIDTH)						// タイトルの幅
#define	RESULT_SIZE_Y			(SCREEN_HEIGHT)						// タイトルの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResult(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureResult = NULL;		// テクスチャへのポインタ

VERTEX_2D				vertexWkResult[NUM_VERTEX];			// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_RESULT,				// ファイルの名前
		&D3DTextureResult);		// 読み込むメモリー

// 頂点情報の作成
	MakeVertexResult();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	if (D3DTextureResult != NULL)
	{// テクスチャの開放
		D3DTextureResult->Release();
		D3DTextureResult = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureResult);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkResult, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResult(void)
{
	// 頂点座標の設定
	vertexWkResult[0].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	vertexWkResult[1].vtx = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y, 0.0f);
	vertexWkResult[2].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);
	vertexWkResult[3].vtx = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkResult[0].rhw =
	vertexWkResult[1].rhw =
	vertexWkResult[2].rhw =
	vertexWkResult[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkResult[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkResult[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkResult[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkResult[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkResult[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

