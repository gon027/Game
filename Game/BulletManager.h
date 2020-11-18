#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "gnLib.h"
#include <memory>

namespace gnGame {

	class Bullet;

	// 最大の数
	constexpr int ListMaxSize = 300;

	using BulletPtr = std::shared_ptr<Bullet>;                // 敵のポインタ
	using BulletList = std::vector<BulletPtr>;  // 敵のポインタのリスト

	class BulletManager
	{
	public:
		static BulletManager* getIns();

	public:
		~BulletManager();

		void addBullet(BulletPtr& _bullet);

		void removeBullet(BulletPtr& _bullet);

		// Update関数を呼び出す
		void onUpdateBulletList();

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
