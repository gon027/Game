#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>
#include <memory>

#include "Actor.h"
#include "Enemy.h"
#include "Player.h"

namespace gnGame {

	using EnemyList = std::vector<UniquePtr<Enemy>>;

	class EnemyManager {
	public:
		// リストにActorを追加
		static void addActor(UniquePtr<Enemy>&& _actor);

		// リストからActorを削除
		static void removeActor(UniquePtr<Enemy> _actor);

		// Start関数を呼び出す
		static void onStartActorList();

		// Mapを登録する
		static void setMap(Map& _map);

		// Update関数を呼び出す
		static void onUpdateActorList();

		// リストのサイズを取得する
		static size_t getListSize() {
			return enemyList.size();
		}

	private:
		static EnemyList enemyList;
	};
}

#endif // !ENEMYMANAGER_H
