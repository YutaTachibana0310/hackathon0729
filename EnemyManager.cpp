#include "main.h"
#include "EnemyManager.h"
#include "debugWindow.h"

#define START_TIMING	(90)	// 何フレームごとに発生するか(初期)
#define MAX_TIMING		(30)	// 発生のスピードの最高

int EnemyManager::s_fireTiming = START_TIMING;

EnemyManager::EnemyManager()
{
	startcnt = 0;
	firetime = START_TIMING;
	s_fireTiming = START_TIMING;
}


EnemyManager::~EnemyManager()
{
	for (auto &e : enemy)
	{
		SAFE_DELETE(e);
	}
	enemy.clear();
	ReleaseVector(enemy);
}

void EnemyManager::Update()
{
	// 使用確認
	Check();

	// セット
	Set();

	// 更新
	for (auto &e : enemy)
	{
		e->Update();
	}

	// デバッグ
	Debug();
}

void EnemyManager::Draw()
{
	// 描画
	for (auto &e : enemy)
	{
		e->Draw();
	}
}

// 使用確認
void EnemyManager::Check()
{
	for (auto e = enemy.begin(); e != enemy.end();)
	{
		if ((*e)->GetUse() == false)
		{
			SAFE_DELETE((*e));
			e = enemy.erase(e);
		}
		else
		{
			e++;
		}
	}
}

// 一定時間ごとに発生
void EnemyManager::Set()
{

	startcnt++;
	if (startcnt == s_fireTiming)
	{
		int random = rand() % 3;

		enemy.push_back(new Enemy(random));

		startcnt = 0;

		s_fireTiming -= 3;
		s_fireTiming = max(s_fireTiming, MAX_TIMING);
	}
}

void EnemyManager::Debug()
{
	int cnt = 0;
	for (auto e = enemy.begin(); e != enemy.end();)
	{
		if ((*e)->GetUse() == true)
		{
			cnt++;
		}
		e++;
	}

	BeginDebugWindow("Enemy");

	DebugText("EnemyCount%d", cnt);

	EndDebugWindow("Enemy");
}