#ifndef _FINISH_H_
#define _FINISH_H_


#include "UIObject.h"
class Finish :
	public UIObject
{
private:
	void MakeVertex();
	void SetTexture();

public:
	Finish();
	~Finish();

	void Update()override;
	void Draw()override;

};

#endif
