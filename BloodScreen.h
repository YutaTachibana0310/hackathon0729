#ifndef _BLOODSCREEN_H_
#define _BLOODSCREEN_H_

#include "UIObject.h"

class BloodScreen :
	public UIObject
{
private:
	static int alpha;	// �A���t�@�l

	void MakeVertex();
	void SetColor();

public:
	BloodScreen();
	~BloodScreen();

	void Update()override;
	void Draw()override;

	static void SetAlpha();	// �A���t�@�l�����Z
};

#endif
