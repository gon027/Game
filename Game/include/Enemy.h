#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"
#include "Map.h"
#include "../EnemyBody.h"

namespace gnGame {

	enum class EnemyActionState {
		Wait,     // �ҋ@
		Action    // �s��(�ړ���U���Ȃǂ͂����B���㕪���邩������Ȃ�)
	};

	// �G�̃^�C�v
	enum class EnemyType {
		Nomal,     // ���ʂ̓G
		Boss,      // �{�X
	};

	// �G�N���X(�x�[�X�N���X)
	class Enemy : public IActor {
	public:
		Enemy();
		Enemy(const Vector2& _pos, const ActorParameter _parameter, const EnemyType _enemyType = EnemyType::Nomal);
		virtual ~Enemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		virtual Vector2 intersectTileMap() override;

		// �}�b�v��ݒ肷��
		void setMap(Map* _map);

		// ���݂̌����Ă���������擾����
		Direction getDir();

		// �G�̃R���C�_�[���擾
		BoxCollider& getCollider();

		// �G�̗̑͂Ȃǂ̏��̃N���X���擾
		EnemyBody& getEnemyBody();

		// �G�̃p�����[�^���擾
		ActorParameter& getParameter();

		// �G�����ʂ̓G���{�X���̃^�C�v���擾����
		const EnemyType getEnemyType();

	protected:
		void moveEnemy();

	protected:
		Map* map;                        // �}�b�v�̃|�C���^
		Direction dir;                   // �����Ă�����p
		Sprite sprite;                   // �摜 (�����\������)
		bool isGround;                   // �n�ʂɂ��Ă��邩
		BoxCollider collider;            // �R���C�_�[
		EnemyBody enemyBody;             // �G�̗̑͏��
		EnemyType enemyType;             // �G�̃^�C�v
		EnemyActionState actionState;    // �G�̍s�����
	};
}

#endif // !ENEMY_H