//=====================================
//
//�T�E���h�G�t�F�N�g�}�l�[�W������[soundEffectManager.cpp]
//Author:GP11A341 21 ���ԗY��
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
�}�N����`
***************************************/
#define SOUND_POS_FAR_END			(10000.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
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
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
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
�I������
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
�X�V����
***************************************/
void UpdateSoundEffectManager(void)
{
	
}

/**************************************
�Đ�����
***************************************/
void PlaySE(DefineSE sound)
{
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, true);
}

/**************************************
��~����
***************************************/
void StopSE(DefineSE sound)
{
	StopSoundBuffer(container[sound].clip);
}

/**************************************
�ĊJ����
***************************************/
void ResumeSE(DefineSE sound)
{
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, false);
}

/**************************************
�Đ�������
***************************************/
bool IsPlayingSE(DefineSE sound)
{
	return IsPlaying(container[sound].clip);
}

/**************************************
���ʐݒ�
***************************************/
void SetSEVolume(DefineSE sound, float volume)
{
	SetSoundVolume(container[sound].clip, volume);
}