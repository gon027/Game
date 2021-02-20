#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "EnemyState.h"
#include "BossState.h"

namespace gnGame {

	class Boss : public Enemy {
	public:
		Boss(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter);
		~Boss();

		void onStart() override;
		void onUpdate() override;

		// �s���p�^�[����ύX����
		void changeState(BossPattern _pattern, float time = 0.0f);

		// ���݂̃{�X�̍s����Ԃ��擾����
		const BossPattern& getBossPattern();

		// 1�O�̃{�X�̍s�����擾����
		const BossPattern getPrevBossPattern();

		// ���p�����߂�
		void setDirection(Direction _dir);

	private:
		GameScene* gameScene;
		BossAction::BossOrderComponent* component;
		BossPattern bossPattern;
		BossPattern prevBossPattern;  // 1�O�̃{�X�̍s��

	public:
		bool isaaajump = false;
	};
}

#endif // !BOSS_H