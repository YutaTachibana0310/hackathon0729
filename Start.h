#ifndef _START_H_
#define _START_H_

#include "UIObject.h"
class Start :
	public UIObject
{
private:
	int cnt;
	int anim;

	void MakeVertex();
	void SetTexture();

public:
	Start();
	~Start();

	void Update()override;
	void Draw()override;

	int Check();
};

#endif
