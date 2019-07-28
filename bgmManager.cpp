//=====================================
//
//BGMマネージャ処理[bgmManager.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "bgmManager.h"
#include "sound.h"
#include <tchar.h>
#include "Framework\Easing.h"
#include "debugWindow.h"
#include <stdio.h>

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
//BGMのファイルへのパス
static const TCHAR* BgmFileName[BGM_MAX] = {
	_T("data/SOUND/LAST_GUARDIAN.wav"),
};

//BGMの音量
static const float bgmVolume[BGM_MAX] = {
	20.0f,
};

static BGM bgmData[BGM_MAX];

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void InitBgmManager(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		BGM *ptr = &bgmData[0];
		for (int i = 0; i < BGM_MAX; i++, ptr++)
		{
			ptr->clip = LoadSound(&BgmFileName[i][0]);
			ptr->volume = bgmVolume[i];
			SetSoundVolume(ptr->clip, ptr->volume);
		}
		initialized = true;
	}
}

/**************************************
終了処理
***************************************/
void UninitBgmManager(int num)
{
	if (num == 0)
	{
		BGM *ptr = &bgmData[0];
		for (int i = 0; i < BGM_MAX; i++, ptr++)
		{
			SAFE_RELEASE(ptr->clip);
		}
	}
}

/**************************************
更新処理
***************************************/
void UpdateBgmManager(void)
{
	BGM *ptr = &bgmData[0];
	for (int i = 0; i < BGM_MAX; i++, ptr++)
	{
		if (ptr->state == BGM_NORMAL)
			continue;

		ptr->cntFrame++;

		//フェード処理
		float t = (float)ptr->cntFrame / (float)ptr->fadeDuration;
		float setVolume;

		if (ptr->state == BGM_FADEIN)
			setVolume = t * ptr->volume;
		else if (ptr->state == BGM_FADEOUT)
			setVolume = (1.0f - t) * ptr->volume;

		SetSoundVolume(ptr->clip, setVolume);

		if (ptr->cntFrame == ptr->fadeDuration)
		{
			if (ptr->state == BGM_FADEOUT)
				StopBGM((DEFINE_BGM)i);

			ptr->state = BGM_NORMAL;
		}
	}
}

/**************************************
再生処理
***************************************/
void PlayBGM(DEFINE_BGM bgm)
{
	SetSoundVolume(bgmData[bgm].clip, bgmData[bgm].volume);
	PlaySoundBuffer(bgmData[bgm].clip, E_DS8_FLAG_LOOP, true);
	bgmData[bgm].state = BGM_NORMAL;
}

/**************************************
停止
***************************************/
void StopBGM(DEFINE_BGM bgm)
{
	StopSoundBuffer(bgmData[bgm].clip);
}

/**************************************
再開
***************************************/
void ResumeBGM(DEFINE_BGM bgm)
{
	PlaySoundBuffer(bgmData[bgm].clip, E_DS8_FLAG_LOOP, false);
}

/**************************************
再生中判定
***************************************/
bool IsPlayingBGM(DEFINE_BGM bgm)
{
	return IsPlaying(bgmData[bgm].clip);
}

/**************************************
フェードイン設定
***************************************/
void FadeInBGM(DEFINE_BGM bgm, int duration, bool isResume)
{
	BGM *ptr = &bgmData[bgm];
	ptr->cntFrame = 0;
	ptr->fadeDuration = duration;
	ptr->state = BGM_FADEIN;

	if (isResume)
		ResumeBGM(bgm);
	else
		PlayBGM(bgm);
}

/**************************************
フェードアウト設定
***************************************/
void FadeOutBGM(DEFINE_BGM bgm, int duration)
{
	BGM *ptr = &bgmData[bgm];
	ptr->cntFrame = 0;
	ptr->fadeDuration = duration;
	ptr->state = BGM_FADEOUT;
}
