#ifndef _TIMER_H_
#define _TIMER_H_

#include "UIObject.h"
#include "Digit.h"

#define TIME_MAX	(3600)			// 制限時間(フレーム数)
#define DIGIT_MAX	(2)

class Timer :
	public UIObject
{
protected:
	Digit * time[DIGIT_MAX];		// それぞれの桁を表示するオブジェクトのポインタ
	DWORD digit[DIGIT_MAX];			// currentTimeをひとけたずつ分解したもの
	DWORD currentTime;

public:
	Timer();
	~Timer();

	void Update()override;
	void Draw()override;

	void Start();
	void Stop();

	DWORD Check();	// 現在時間の確認

	bool GetUse() { return use; };
};

#endif
