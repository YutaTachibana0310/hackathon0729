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
enum DefineSE
{
	//�T�E���h�ʂ��i���o�[
	SE_KICK,
	SE_BUTTON,
	SE_MAX
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