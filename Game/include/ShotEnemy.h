#ifndef SHOTENEMY_H
#define SHOTENEMY_H

#include "Enemy.h"
#include "EnemyState.h"
#include "FrameTimer.h"

namespace gnGame {

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
	};

}

#endif // !SHOTENEMY_H