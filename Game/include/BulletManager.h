#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <memory>
#include "gnLib.h"

namespace gnGame {

	namespace {
		// 最大の数
		constexpr int ListMaxSize = 100;
	}
	
	class Bullet;
	class Map;
	class Player;
	class GameScene;

	using BulletPtr = std::shared_ptr<Bullet>;                // 敵のポインタ
	using BulletList = std::vector<BulletPtr>;  // 敵のポインタのリスト

	class BulletManager
	{
	public:
		static BulletManager* getIns();

	public:
		~BulletManager();

		// 弾を追加
		void addBullet(BulletPtr& _bullet);

		// Update関数を呼び出す
		void onUpdateBulletList();

		// 敵との衝突判定
		void collisionActor(Player& _player, GameScene* _gameScene);

		// マップとの衝突判定
		void collisionMap(Map& _map);

		// 配列を空にする
		void claerList();

		// リストのサイズを取得する
		size_t getListSize() {
			return bulletList.size();
		}

	private:
		BulletManager() : bulletList(ListMaxSize) {};
		BulletManager(const BulletManager&);
		BulletManager& operator= (const BulletManager&);

	private:
		BulletList bulletList;
	};

}

#endif // !BULLETMANAGER_H
