#ifndef _DIGIT_H_
#define _DIGIT_H_

#include "UIObject.h"
class Digit :
	public UIObject
{
protected:
	static LPDIRECT3DTEXTURE9 D3DTexture;	// �e�N�X�`���̃|�C���^
	DWORD time;								// ���̌��ɕ\�����鐔���i0-9 or 0-5�j

	void MakeVertex();
	void SetTexture();


public:
	Digit(int digit);
	~Digit();

	void Update()override;
	void Digit::Update(DWORD time);
	void Draw()override;
};

#endif
