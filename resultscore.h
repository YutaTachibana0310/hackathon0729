//=============================================================================
//
// リザルトスコア処理 [resultscore.h]
// Author : 染矢　晃介
//
//=============================================================================
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_
//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_GAME_RESULT_SCORE	"data/TEXTURE/number.png"			// スコア用画像

#define TEXTURE_RESULT_SCORE_SIZE_X				(300)					// スコアテクスチャサイズ
#define TEXTURE_RESULT_SCORE_SIZE_Y				(300)					// 同上

#define RESULT_SCORE_POS_X						(1100)					// スコアの初期位置X
#define RESULT_SCORE_POS_Y						(300)					// 同上

#define RESULT_SCORE_WIDE						(150)                    //数字の幅
#define RESULT_SCORE_MAX						(99999)					// スコアの最大値
#define RESULT_SCORE_DIGIT						(5)						// 桁数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultScore(void);
void UninitResultScore(void);
void UpdateResultScore(void);
void DrawResultScore(void);
void SetResultScore(int num);

#endif
