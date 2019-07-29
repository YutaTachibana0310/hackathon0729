#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Framework\BoardPolygon.h"
#include "Framework\BoxCollider3D.h"

#define ENEMY_POLYGON_SIZE	D3DXVECTOR2(20.0f, 20.0f)
#define ENEMY_COLLIDER_SIZE	D3DXVECTOR3(15.0f, 15.0f, 0.0f)

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

	BoxCollider3D *bodyCollider;

private:
	BoardPolygon * polygon;
	Transform transform;

	bool	use;

};

#endif
