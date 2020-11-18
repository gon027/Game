#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>
#include <memory>

#include "Actor.h"
#include "Enemy.h"
#include "Player.h"

namespace gnGame {

	// 最大の数
	constexpr int MaxSize = 100;

	using EnemyPtr = std::shared_ptr<Enemy>;                // 敵のポインタ
	using EnemyList = std::vector<EnemyPtr>;  // 敵のポインタのリスト

	class EnemyManager {
	public:
		static EnemyManager* getIns();

	public:
		~EnemyManager();

		// リストにActorを追加
		void addActor(EnemyPtr& _enemy);

		// リストからActorを削除
		void removeActor(EnemyPtr& _enemy);

		// Start関数を呼び出す
		void onStartEnemyList();

		// Mapを登録する
		void setMap(Map& _map);

		// Update関数を呼び出す
		void onUpdateActorList();

		// 配列を空にする
		void claerList();

		// リストのサイズを取得する
		size_t getListSize() {
			return enemyList.size();
		}

	private:
		EnemyManager() : enemyList(MaxSize) {};
		EnemyManager(const EnemyManager&);
		EnemyManager& operator= (const EnemyManager&);

	private:
		EnemyList enemyList;
	};
}

#endif // !ENEMYMANAGER_H
