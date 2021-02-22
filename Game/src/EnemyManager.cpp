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

	void EnemyManager::onUpdateEnemyList()
	{
		static Font font{ 24, "MS 明朝" };
		
		int i{ 0 };
		for (auto& enemy : enemyList) {
			if (enemy) {
				enemy->onUpdate();
				font.drawText(0, 200 + 24 * i, Color::Black, "Pos = %s", enemy->getVelocity().toString().c_str());
				i++;
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
				_player.getPlayerBody().damage(2);

				if (_player.getPlayerBody().getParameter().hp <= 0) {
					_player.death();
				}
			}
		}
	}

	void EnemyManager::claerList()
	{
		// 配列をnullptrで埋める
		for (size_t i{ 0 }; i < enemyList.size(); ++i) {
			if (enemyList[i]) {
				enemyList[i] = nullptr;
			}
		}
	}

}
