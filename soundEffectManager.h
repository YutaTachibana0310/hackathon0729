//=====================================
//
//�T�E���h�G�t�F�N�g�}�l�[�W���w�b�_[soundEffectManager.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _SOUNDEFFECTMANAGER_H_
#define _SOUNDEFFECTMANAGER_H_

#include "main.h"

#include <dsound.h>
#include <mmsystem.h>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define SOUND_VOLUME_MAX	(100.0f)		//�ő剹��
#define SOUND_VOLUME_MIN	(0.0f)			//�ŏ�����

/**************************************
�\���̒�`
***************************************/
enum class  DefineSE : unsigned int
{
	//�T�E���h�ʂ��i���o�[
	LOCKON,
	MISSILELAUNCH,
	SMALLEXPL,
	READY,
	DECISION,
	SHOT,
	MIDDLEEXPL,
	BONUSEXPL,
	BONUSSTART,
	NORMALEXPL,
	CURSOR,
	POWERUP,
	HOMINGBULLET,
	ENEMYBULLET,
	MENUDICISION,
	PAUSE,
	CAUTION,
	NOISE,
	MAX
};

typedef struct
{
	LPDIRECTSOUNDBUFFER8 clip;
	bool playOrder;
	float volume;
}SOUNDEFFECT;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitSoundEffectManager(int num);
void UninitSoundEffectManager(int num);
void UpdateSoundEffectManager(void);

void PlaySE(DefineSE sound);
void PlaySE_3D(DefineSE sound, float posZ);
void StopSE(DefineSE sound);
void ResumeSE(DefineSE sound);
bool IsPlayingSE(DefineSE sound);

#endif