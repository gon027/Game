#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>
#include <memory>

#include "Enemy.h"

namespace gnGame {

	class Player;

	// �ő�̐�
	constexpr int MaxSize = 50;

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
		void removeActor(size_t _index);

		// Start�֐����Ăяo��
		void onStartEnemyList();

		// Map��o�^����
		void setMap(Map& _map);

		// Update�֐����Ăяo��
		void onUpdateActorList();

		// �v���C���[�Ƃ̓����蔻��
		void collisionPlayer(Player& _player);

		// �z�����ɂ���
		void claerList();

		// �G���X�g�̎Q�Ƃ��擾����
		EnemyList& getEnemyList() {
			return enemyList;
		}

		EnemyPtr& getEnemy(size_t _index) {
			return enemyList[_index];
		}

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
