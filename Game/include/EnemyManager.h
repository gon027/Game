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
		// ���X�g��Actor��ǉ�
		static void addActor(UniquePtr<Enemy>&& _actor);

		// ���X�g����Actor���폜
		static void removeActor(UniquePtr<Enemy> _actor);

		// Start�֐����Ăяo��
		static void onStartActorList();

		// Map��o�^����
		static void setMap(Map& _map);

		// Update�֐����Ăяo��
		static void onUpdateActorList();

		// ���X�g�̃T�C�Y���擾����
		static size_t getListSize() {
			return enemyList.size();
		}

	private:
		static EnemyList enemyList;
	};
}

#endif // !ENEMYMANAGER_H
