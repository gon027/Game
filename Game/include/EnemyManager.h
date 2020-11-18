#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>
#include <memory>

#include "Actor.h"
#include "Enemy.h"
#include "Player.h"

namespace gnGame {

	// �ő�̐�
	constexpr int MaxSize = 100;

	using EnemyPtr = std::shared_ptr<Enemy>;                // �G�̃|�C���^
	using EnemyList = std::vector<EnemyPtr>;  // �G�̃|�C���^�̃��X�g

	class EnemyManager {
	public:
		static EnemyManager* getIns();

	public:
		~EnemyManager();

		// ���X�g��Actor��ǉ�
		void addActor(EnemyPtr& _enemy);

		// ���X�g����Actor���폜
		void removeActor(EnemyPtr& _enemy);

		// Start�֐����Ăяo��
		void onStartEnemyList();

		// Map��o�^����
		void setMap(Map& _map);

		// Update�֐����Ăяo��
		void onUpdateActorList();

		// �z�����ɂ���
		void claerList();

		// ���X�g�̃T�C�Y���擾����
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
