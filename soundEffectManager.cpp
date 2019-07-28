//=====================================
//
//サウンドエフェクトマネージャ処理[soundEffectManager.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "soundEffectManager.h"
#include "sound.h"
#include <tchar.h>
#include "debugWindow.h"
#include <stdio.h>

#include <vector>

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

/**************************************
マクロ定義
***************************************/
#define SOUND_POS_FAR_END			(10000.0f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static const TCHAR* soundFileName[SE_MAX] =
{
	_T("data/SOUND/lockon.wav"),
};

static const float soundVolume[SE_MAX] = {
	1.0f,
};

static vector<SOUNDEFFECT> container;

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void InitSoundEffectManager(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		container.resize(SE_MAX);
		for(int i = 0; i < SE_MAX; i++)
		{
			container[i].clip = LoadSound(&soundFileName[i][0]);
			container[i].volume = soundVolume[i];
			SetSoundVolume(container[i].clip, container[i].volume);
		}

		initialized = true;
	}

	return;
}

/**************************************
終了処理
***************************************/
void UninitSoundEffectManager(int num)
{
	if (num == 0)
	{
		for (auto& se : container)
		{
			SAFE_RELEASE(se.clip);
		}
	}
}

/**************************************
更新処理
***************************************/
void UpdateSoundEffectManager(void)
{
	
}

/**************************************
再生処理
***************************************/
void PlaySE(DefineSE sound)
{
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, true);
}

/**************************************
停止処理
***************************************/
void StopSE(DefineSE sound)
{
	StopSoundBuffer(container[sound].clip);
}

/**************************************
再開処理
***************************************/
void ResumeSE(DefineSE sound)
{
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, false);
}

/**************************************
再生中判定
***************************************/
bool IsPlayingSE(DefineSE sound)
{
	return IsPlaying(container[sound].clip);
}

/**************************************
音量設定
***************************************/
void SetSEVolume(DefineSE sound, float volume)
{
	SetSoundVolume(container[sound].clip, volume);
}