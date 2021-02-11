#ifndef SHOTENEMY_H
#define SHOTENEMY_H

#include "Enemy.h"
#include "EnemyState.h"
#include "FrameTimer.h"

namespace gnGame {

	namespace EnemyState {

		/// <summary>
		/// ShotEnemy�̍U���p�^�[��
		/// </summary>
		class BulletShotPattern1 : public Attack::EnemyAttack {
		private:
			const float InterVal = 5.0f;

		public:
			BulletShotPattern1(Enemy* _enemyPtr);
			~BulletShotPattern1() = default;

			virtual void execute() override;

		private:
			FrameTimer frameTimer;
			Player* player;
		};
	}

	/// <summary>
	/// �e����G
	/// ���̏ꂩ�瓮�����e�����
	/// </summary>
	class ShotEnemy : public Enemy {
	public:
		ShotEnemy();
		ShotEnemy(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter);
		virtual ~ShotEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		void action();

	private:
		GameScene* gameScene;
		FrameTimer frameTime;
		AnimSprite waitAnimSprite;    // �ҋ@�p�̉摜
		AnimSprite actionAnimSprite;  // �A�j���[�V�����p�̉摜
		EnemyState::Attack::AimedShotPlayer enemyAttack;
		//EnemyState::BulletShotPattern1 bShotPattern1;
	};

}

#endif // !SHOTENEMY_H