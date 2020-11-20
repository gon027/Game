#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>
#include <memory>

#include "Enemy.h"

namespace gnGame {

	class Player;

	// 最大の数
	constexpr int MaxSize = 50;

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
		void removeActor(size_t _index);

		// Start関数を呼び出す
		void onStartEnemyList();

		// Mapを登録する
		void setMap(Map& _map);

		// Update関数を呼び出す
		void onUpdateActorList();

		// プレイヤーとの当たり判定
		void collisionPlayer(Player& _player);

		// 配列を空にする
		void claerList();

		// 敵リストの参照を取得する
		EnemyList& getEnemyList() {
			return enemyList;
		}

		EnemyPtr& getEnemy(size_t _index) {
			return enemyList[_index];
		}

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
