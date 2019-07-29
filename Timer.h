#ifndef _TIMER_H_
#define _TIMER_H_

#include "UIObject.h"
#include "Digit.h"

#define TIME_MAX	(3600)			// ��������(�t���[����)
#define DIGIT_MAX	(2)

class Timer :
	public UIObject
{
protected:
	Digit * time[DIGIT_MAX];		// ���ꂼ��̌���\������I�u�W�F�N�g�̃|�C���^
	DWORD digit[DIGIT_MAX];			// currentTime���ЂƂ�����������������
	DWORD currentTime;

public:
	Timer();
	~Timer();

	void Update()override;
	void Draw()override;

	void Start();
	void Stop();

	DWORD Check();	// ���ݎ��Ԃ̊m�F

	bool GetUse() { return use; };
};

#endif
