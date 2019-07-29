//=============================================================================
//
// スコア処理 [score.h]
// Author : 染矢　晃介
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_GAME_SCORE	"data/TEXTURE/number.png"			// スコア用画像
#define TEXTURE_GAME_ROGO	"data/TEXTURE/rogo.png"				// スコアロゴ用画像

#define TEXTURE_SCORE_SIZE_X			(100)					// スコアテクスチャサイズ
#define TEXTURE_SCORE_SIZE_Y			(100)					// 同上
#define TEXTURE_SCORE_ROGO_SIZE_X		(100)					// スコアテクスチャサイズ
#define TEXTURE_SCORE_ROGO_SIZE_Y		(100)					// 同上

#define SCORE_POS_X						(1400)					// スコアの初期位置X
#define SCORE_POS_Y						(10)					// 同上
#define SCORE_ROGO_POS_X				(1100)					// スコアロゴの初期位置Y
#define SCORE_ROGO_POS_Y				(10)					// 同上

#define SCORE_WIDE				(50)                            //数字の幅
#define SCORE_MAX				(99999)							// スコアの最大値
#define SCORE_DIGIT				(5)								// 桁数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int num);

#endif
