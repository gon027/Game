#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "gnLib.h"
#include <memory>

namespace gnGame {

	class Bullet;

	// �ő�̐�
	constexpr int ListMaxSize = 300;

	using BulletPtr = std::shared_ptr<Bullet>;                // �G�̃|�C���^
	using BulletList = std::vector<BulletPtr>;  // �G�̃|�C���^�̃��X�g

	class BulletManager
	{
	public:
		static BulletManager* getIns();

	public:
		~BulletManager();

		void addBullet(BulletPtr& _bullet);

		void removeBullet(BulletPtr& _bullet);

		// Update�֐����Ăяo��
		void onUpdateBulletList();

		void claerList();

		// ���X�g�̃T�C�Y���擾����
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
