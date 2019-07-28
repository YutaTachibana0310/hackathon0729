//=====================================
//
//ヘキサトランジション処理[HexaTransition.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "HexaTransition.h"

/**************************************
マクロ定義
***************************************/
#define HEXATRANSITION_DURATION		(45)

/**************************************
更新処理
***************************************/
void HexaTransition::Update()
{
	if (!enableMask)
		return;

	cntFrame++;

	//マスク画像のスケールをイージングする
	float t = 1.f * cntFrame / HEXATRANSITION_DURATION;
	transform.scale = Easing<D3DXVECTOR3>::GetEasingValue(t, &initScale, &goalScale, easeType);

	//回転させる
	transform.Rotate(0.0f, 0.0f, 5.0f);

	//トランジションの終了確認
	if (cntFrame == HEXATRANSITION_DURATION)
	{
		//マスクをオフに
		enableMask = false;

		//遷移後であればトランジション画像をオフに
		if (isTransitionOut)
			enableTransition = false;

		//コールバックの呼び出し
		if(callback != NULL)
			callback();

		callback = NULL;
	}
}

/**************************************
トランジション開始処理
***************************************/
void HexaTransition::SetTransition(bool isStart, std::function<void(void)> func)
{
	//すでにマスク中であれば開始しない
	if (enableMask)
		return;

	//同じ遷移状態は開始しない
	if (isStart == enableTransition)
		return;

	//イージング用のパラメータ初期化
	initScale = isStart ? D3DXVECTOR3(1.0f, 1.0f, 1.0f) : D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	goalScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f) - initScale;
	easeType = isStart ? OutExponential : InExponential;
	cntFrame = 0;

	//コールバック登録
	callback = func;

	//フラグ初期化
	enableMask = true;
	enableTransition = true;
	isTransitionOut = !isStart;
}

