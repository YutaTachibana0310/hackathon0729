#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

#include "Enemy.h"

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;
	int startcnt;				// �����܂ł̃J�E���g�A�b�v

	void Set();
	void Check();

	void Debug();

public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Draw();
};

#endif