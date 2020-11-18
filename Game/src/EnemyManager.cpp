#include "../include/EnemyManager.h"

namespace gnGame {

	EnemyManager* EnemyManager::getIns()
	{
		static EnemyManager Instance;
		return &Instance;
	}

	EnemyManager::~EnemyManager()
	{

	}

	void EnemyManager::addActor(EnemyPtr& _enemy)
	{
		for (auto i{ 0 }; i < enemyList.size(); ++i) {
			if (!enemyList[i]) {
				enemyList[i] = _enemy;
				return;
			}
		}

		enemyList.emplace_back(_enemy);
	}

	void EnemyManager::removeActor(EnemyPtr& _enemy)
	{

	}

	void EnemyManager::onStartEnemyList()
	{
		for (auto& enemy : enemyList) {
			if (enemy) {
				enemy->onStart();
			}
		}
	}

	void EnemyManager::setMap(Map& _map)
	{
		for (auto& enemy : enemyList) {
			if (enemy) {
				enemy->setMap(_map);
			}
		}
	}

	void EnemyManager::onUpdateActorList()
	{
		float i{ 1.82f };
		for ( auto& enemy : enemyList) {
			if (enemy) {
				enemy->onUpdate(i);
				i += 0.46f;
			}
		}
	}

	void EnemyManager::claerList()
	{
		enemyList.clear();
	}

}
