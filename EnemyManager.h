#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

#include "Enemy.h"

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;
	int startcnt;				// 発生までのカウントアップ
	int firetime;				// 発射するタイミング

	void Set();
	void Check();

	void Debug();

public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Draw();

	static int s_fireTiming;
};

#endif
