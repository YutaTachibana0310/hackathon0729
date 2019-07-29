//=====================================
//
//背景[BG.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "Framework\BoardPolygon.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
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