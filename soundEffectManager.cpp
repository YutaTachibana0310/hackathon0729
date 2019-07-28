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
#include <type_traits>

#include <map>

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
static const TCHAR* soundFileName[static_cast<unsigned int>(DefineSE::MAX)] =
{
	_T("data/SOUND/lockon.wav"),
	_T("data/SOUND/burst00.wav"),
	_T("data/SOUND/don18_B.wav"),
	_T("data/SOUND/ready.wav"),
	_T("data/SOUND/decision16.wav"),
	_T("data/SOUND/gun29.wav"),
	_T("data/SOUND/bom16.wav"),
	_T("data/SOUND/magic-ice1.wav"),
	_T("data/SOUND/magic-attack-holy1.wav"),
	_T("data/SOUND/bom30.wav"),
	_T("data/SOUND/cursor2.wav"),
	_T("data/SOUND/decision24.wav"),
	_T("data/SOUND/shoot13.wav"),
	_T("data/SOUND/shoot09.wav"),
	_T("data/SOUND/decision9.wav"),
	_T("data/SOUND/decision26.wav"),
	_T("data/SOUND/data-analysis2.wav"),
	_T("data/SOUND/noise.wav")
};

static const map<DefineSE, string> defSEname = {
	{ DefineSE::LOCKON, STR(LOCKON)},
	{ DefineSE::MISSILELAUNCH,STR(MISSILELAUNCH) },
	{ DefineSE::SMALLEXPL, STR(SMALLEXPL) },
	{ DefineSE::READY, STR(READY) },
	{ DefineSE::DECISION,STR(DECISION) },
	{ DefineSE::SHOT,STR(SHOT) },
	{ DefineSE::MIDDLEEXPL,STR(MIDDLEEXPL) },
	{ DefineSE::BONUSEXPL, STR(BONUSEXPL) },
	{ DefineSE::BONUSSTART,STR(BONUSSTART) },
	{ DefineSE::NORMALEXPL, STR(NORMALEXPL) },
	{ DefineSE::CURSOR,STR(CURSOR) },
	{ DefineSE::POWERUP, STR(POWEUP)},
	{ DefineSE::HOMINGBULLET, STR(HOMINGBULLET)},
	{ DefineSE::ENEMYBULLET, STR(ENEMYBULLET)},
	{ DefineSE::MENUDICISION, STR(MENUDICISION)},
	{ DefineSE::PAUSE, STR(PAUSE)},
	{ DefineSE::CAUTION, STR(CAUTION)},
	{ DefineSE::NOISE, STR(NOISE) },
	{ DefineSE::MAX, STR(MAX) },
};

//static SOUNDEFFECT se[static_cast<unsigned int>(DefineSE::MAX)];
static map<DefineSE, SOUNDEFFECT> container;

/**************************************
�v���g�^�C�v�錾
***************************************/
bool SaveSettingsSoundEffect(void);
bool LoadSettingsSoundEffect(void);
void DrawDebugWindowSoundEffect(void);

DefineSE begin(DefineSE) { return DefineSE::LOCKON; }
DefineSE end(DefineSE) { return DefineSE::MAX; }
DefineSE operator*(DefineSE se) { return se; }
DefineSE operator++(DefineSE& se) {
	return se = DefineSE(underlying_type<DefineSE>::type(se) + 1);
}

/**************************************
����������
***************************************/
void InitSoundEffectManager(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		bool res = LoadSettingsSoundEffect();

		for (auto i : DefineSE())
		{
			container[i].clip = LoadSound(&soundFileName[static_cast<unsigned int>(i)][0]);
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
		for (auto i : DefineSE())
		{
			SAFE_RELEASE(container[i].clip);
		}
	}
}

/**************************************
�X�V����
***************************************/
void UpdateSoundEffectManager(void)
{
	DrawDebugWindowSoundEffect();
}

/**************************************
�Đ�����
***************************************/
void PlaySE(DefineSE sound)
{
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, true);
}

/**************************************
�Đ�����(3D��)
***************************************/
void PlaySE_3D(DefineSE sound, float posZ)
{
	float decay = 1.0f - posZ / SOUND_POS_FAR_END;

	SetSoundVolume(container[sound].clip, container[sound].volume * decay);
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

/**************************************
�f�o�b�O�E�B���h�E
***************************************/
void DrawDebugWindowSoundEffect(void)
{
	BeginDebugWindow("SoundEffect");
	DebugText("SoundNum : %d", container.size());

	for (auto i : DefineSE())
	{
		DebugSliderFloat(&defSEname.at(i), &container[i].volume, SOUND_VOLUME_MIN, SOUND_VOLUME_MAX);
	}

	if (DebugButton("Save Settings"))
	{
		SaveSettingsSoundEffect();
		for (auto i : DefineSE())
		{
			SetSoundVolume(container[i].clip, container[i].volume);
		}
	}

	EndDebugWindow("SoundEffect");

	BeginDebugWindow("PlaySound");

	for (auto i : DefineSE())
	{
		if (DebugButton(&defSEname.at(i))) { PlaySE(i); }
	}

	EndDebugWindow("PlaySound");
}

/**************************************
�ݒ�ۑ�����
***************************************/
bool SaveSettingsSoundEffect(void)
{
	FILE *fp = NULL;
	fp = fopen("data/SETTINGS/sound.ini", "wb");

	if (fp == NULL)
	{
		return false;
	}

	for (auto i : DefineSE())
	{
		fwrite(&container[i].volume, sizeof(float), 1, fp);
	}

	fclose(fp);

	return true;
}

/**************************************
�ݒ�ǂݍ��ݏ���
***************************************/
bool LoadSettingsSoundEffect(void)
{
	FILE *fp = NULL;
	fp = fopen("data/SETTINGS/sound.ini", "rb");

	if (fp == NULL)
	{
		for (auto i : DefineSE())
		{
			container[i].volume = SOUND_VOLUME_INIT;
		}

		return false;
	}

	for (auto i : DefineSE())
	{
		int res = fread(&container[i].volume, sizeof(float), 1, fp);
		if (res == EOF)
			container[i].volume = SOUND_VOLUME_INIT;
	}

	fclose(fp);

	return true;
}