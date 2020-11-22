#include "../include/EnemyManager.h"
#include "../include/Player.h"
#include "../include/Enemy.h"

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

	void EnemyManager::removeActor(size_t _index)
	{
		if (!enemyList[_index]) {
			return;
		}

		enemyList[_index] = nullptr;
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

	void EnemyManager::onUpdateEnemyList()
	{
		//Debug::drawFormatText(0, 180, Color::Black, "EnemyList = %d", enemyList.size());
		for (auto& enemy : enemyList) {
			if (enemy) {
				enemy->onUpdate();
			}
		}
	}

	void EnemyManager::collisionPlayer(Player& _player)
	{
		for (auto& enemy : enemyList) {
			if (!enemy) {
				continue;
			}

			if (enemy->getCollider().isHitTest(_player.getCollider())) {
				_player.setActive(false);
				//_player.appryDamage(1);
				//enemy = nullptr;
			}
		}
	}

	void EnemyManager::claerList()
	{
		enemyList.clear();
	}

}
