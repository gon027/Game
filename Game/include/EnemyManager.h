#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>
#include <memory>

namespace gnGame {

	class Map;
	class Player;
	class Enemy;

	// �ő�̐�
	constexpr int MaxEnemyListSize = 50;

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
		void onUpdateEnemyList();

		// �v���C���[�Ƃ̓����蔻��
		void collisionPlayer(Player& _player);

		// �z�����ɂ���
		void claerList();

		// �G���擾����
		EnemyPtr& getEnemy(size_t _index) {
			return enemyList[_index];
		}

		// ���X�g�̃T�C�Y���擾����
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
