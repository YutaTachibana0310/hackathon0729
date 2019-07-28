//=====================================
//
//BGM�}�l�[�W������[bgmManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "bgmManager.h"
#include "sound.h"
#include <tchar.h>
#include "Framework\Easing.h"
#include "debugWindow.h"
#include <stdio.h>

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static const TCHAR* BgmFileName[BGM_MAX] = {
	_T("data/SOUND/LAST_GUARDIAN.wav"),
	_T("data/SOUND/Sword_dance.wav"),
	_T("data/SOUND/P.L.A.Y..wav"),
	_T("data/SOUND/Landing+On+The+Moon_jingle.wav"),
	_T("data/SOUND/gameover2.wav"),
	_T("data/SOUND/To_the_Next_Generation.wav"),
	_T("data/SOUND/Traffic_Jam.wav"),
};

static BGM bgmData[BGM_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/
bool SaveSettingsBGM(void);
bool LoadSettingsBGM(void);
void DrawDebugWindowBGM(void);

/**************************************
����������
***************************************/
void InitBgmManager(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		bool res = LoadSettingsBGM();

		BGM *ptr = &bgmData[0];
		for (int i = 0; i < BGM_MAX; i++, ptr++)
		{
			ptr->clip = LoadSound(&BgmFileName[i][0]);
			SetSoundVolume(ptr->clip, ptr->volume);
		}
		initialized = true;
	}
}

/**************************************
�I������
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
�X�V����
***************************************/
void UpdateBgmManager(void)
{
	BGM *ptr = &bgmData[0];
	for (int i = 0; i < BGM_MAX; i++, ptr++)
	{
		if (ptr->state == BGM_NORMAL)
			continue;

		ptr->cntFrame++;

		//�t�F�[�h����
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

	DrawDebugWindowBGM();
}

/**************************************
�Đ�����
***************************************/
void PlayBGM(DEFINE_BGM bgm)
{
	SetSoundVolume(bgmData[bgm].clip, bgmData[bgm].volume);
	PlaySoundBuffer(bgmData[bgm].clip, E_DS8_FLAG_LOOP, true);
	bgmData[bgm].state = BGM_NORMAL;
}

/**************************************
��~
***************************************/
void StopBGM(DEFINE_BGM bgm)
{
	StopSoundBuffer(bgmData[bgm].clip);
}

/**************************************
�ĊJ
***************************************/
void ResumeBGM(DEFINE_BGM bgm)
{
	PlaySoundBuffer(bgmData[bgm].clip, E_DS8_FLAG_LOOP, false);
}

/**************************************
�Đ�������
***************************************/
bool IsPlayingBGM(DEFINE_BGM bgm)
{
	return IsPlaying(bgmData[bgm].clip);
}

/**************************************
�t�F�[�h�C���ݒ�
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
�t�F�[�h�A�E�g�ݒ�
***************************************/
void FadeOutBGM(DEFINE_BGM bgm, int duration)
{
	BGM *ptr = &bgmData[bgm];
	ptr->cntFrame = 0;
	ptr->fadeDuration = duration;
	ptr->state = BGM_FADEOUT;
}

/**************************************
�f�o�b�O�E�B���h�E
***************************************/
void DrawDebugWindowBGM(void)
{
}

/**************************************
�ݒ�ۑ�����
***************************************/
bool SaveSettingsBGM(void)
{
	FILE *fp = NULL;

	fp = fopen("data/SETTINGS/bgm.ini", "wb");

	if (fp == NULL)
	{
		return false;
	}

	BGM *ptr = &bgmData[0];
	for (int i = 0; i < BGM_MAX;i++, ptr++)
	{
		fwrite(&ptr->volume, sizeof(float), 1, fp);
	}

	fclose(fp);
	return true;
}

/**************************************
�ݒ�ǂݍ��ݏ���
***************************************/
bool LoadSettingsBGM(void)
{
	FILE *fp = NULL;

	//fp = fopen("data/SETTINGS/bgm.ini", "rb");
	if (fp == NULL)
	{
		BGM *ptr = &bgmData[0];
		for (int i = 0; i < BGM_MAX; i++, ptr++)
		{
			ptr->volume = SOUND_VOLUME_INIT;
		}
		return false;
	}

	BGM *ptr = &bgmData[0];
	for (int i = 0; i < BGM_MAX; i++, ptr++)
	{
		int res = fread(&ptr->volume, sizeof(float), 1, fp);
		if (res == EOF)
			ptr->volume = SOUND_VOLUME_INIT;
	}

	return true;
}
