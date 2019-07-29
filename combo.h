//=============================================================================
// コンボ処理 [combo.h]
// Author : 染矢　晃介
//=============================================================================
#ifndef _COMBO_H_
#define _COMBO_H_
//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_GAME_COMBO	"data/TEXTURE/number.png"			    // コンボ用画像
#define TEXTURE_GAME_COMBO_ROGO	"data/TEXTURE/comborogo.png"		// コンボロゴ用画像

#define TEXTURE_COMBO_SIZE_X		(100)							// コンボテクスチャサイズ
#define TEXTURE_COMBO_SIZE_Y		(100)							// 同上
#define TEXTURE_COMBO_ROGO_SIZE_X	(100)							// コンボロゴテクスチャサイズ
#define TEXTURE_COMBO_ROGO_SIZE_Y	(100)							// 同上

#define COMBO_POS_X					(1700)							// コンボの初期位置X
#define COMBO_POS_Y					(10)							// 同上
#define COMBO_ROGO_POS_X			(1500)							// コンボの初期位置X
#define COMBO_ROGO_POS_Y			(10)							// 同上

#define COMBO_WIDE					(50)                            //数字の幅
#define COMBO_MAX					(999)							// コンボの最大値
#define COMBO_DIGIT					(3)								// 桁数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCombo();
void UninitCombo(void);
void UpdateCombo(void);
void DrawCombo(void);
void SetCombo(int num);

#endif

