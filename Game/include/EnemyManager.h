#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>
#include <memory>

namespace gnGame {

	class Map;
	class Player;
	class Enemy;

	// 最大の数
	constexpr int MaxEnemyListSize = 50;

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
		void onUpdateEnemyList();

		// プレイヤーとの当たり判定
		void collisionPlayer(Player& _player);

		// 配列を空にする
		void claerList();

		// 敵を取得する
		EnemyPtr& getEnemy(size_t _index) {
			return enemyList[_index];
		}

		// リストのサイズを取得する
		size_t getListSize() {
			return enemyList.size();
		}

	private:
		EnemyManager() : enemyList(MaxEnemyListSize) {};
		EnemyManager(const EnemyManager&);
		EnemyManager& operator= (const EnemyManager&);

	private:
		EnemyList enemyList;
	};
}

#endif // !ENEMYMANAGER_H
