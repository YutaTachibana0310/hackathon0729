#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Framework\BoardPolygon.h"

class Enemy
{
public:
	Enemy(int num);
	~Enemy();

	void Update();
	void Draw();

	void Check();

	bool GetUse() { return use; };
	void SetUse(bool use) { this->use = use; };

private:
	BoardPolygon * polygon;
	Transform transform;

	bool	use;

};

#endif
