//=====================================
//
//�w�i[BG.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "Framework\BoardPolygon.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class BG
{
public:
	BG();
	~BG();

	void Init();
	void Draw();

	BoardPolygon *polygon;
	Transform transform;
};

#endif