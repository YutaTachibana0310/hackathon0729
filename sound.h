#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

// �}�N����`
#define SOUND_VOLUME_MAX	(100.0f)		//���ʍő�%
#define SOUND_VOLUME_MIN	(0.0f)			//���ʍŏ�%
#define SOUND_VOLUME_INIT	(50.0f)			//��������

enum
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

HRESULT					InitSound(HWND hWnd);	// ������
void					UninitSound();			// ��Еt��
LPDIRECTSOUNDBUFFER8	LoadSound(const TCHAR *path);	// �T�E���h�̃��[�h
void					PlaySoundBuffer(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0, bool fromHead = false);	// �����ƂɍĐ�
void					StopSoundBuffer(LPDIRECTSOUNDBUFFER8 pBuffer);					// �����~�߂�
bool					IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);					// �Đ������ǂ���
void					SetSoundVolume(LPDIRECTSOUNDBUFFER8 pBuffer, float volume);	// �T�E���h�̃{�����[���ݒ�֐�
#endif