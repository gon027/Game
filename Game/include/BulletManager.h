#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <memory>
#include "gnLib.h"
#include "EnemyManager.h"

namespace gnGame {

	// �ő�̐�
	constexpr int ListMaxSize = 100;
	
	class Bullet;
	class Map;
	class Player;

	using BulletPtr = std::shared_ptr<Bullet>;                // �G�̃|�C���^
	using BulletList = std::vector<BulletPtr>;  // �G�̃|�C���^�̃��X�g

	class BulletManager
	{
	public:
		static BulletManager* getIns();

	public:
		~BulletManager();

		// �e��ǉ�
		void addBullet(BulletPtr& _bullet);

		// �e���폜
		void removeBullet(BulletPtr& _bullet);

		// Update�֐����Ăяo��
		void onUpdateBulletList();

		// �G�Ƃ̏Փ˔���
		void collisionActor(EnemyPtr& _enemy, Player& _plyaer);

		// �}�b�v�Ƃ̏Փ˔���
		void collisionMap(Map& _map);

		// �z�����ɂ���
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
