#ifndef _BLOODSCREEN_H_
#define _BLOODSCREEN_H_

#include "UIObject.h"

class BloodScreen :
	public UIObject
{
private:
	static int alpha;	// アルファ値

	void MakeVertex();
	void SetColor();

public:
	BloodScreen();
	~BloodScreen();

	void Update()override;
	void Draw()override;

	static void SetAlpha();	// アルファ値を加算
};

#endif
