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

		// 行動パターンを変更する
		void changeState(BossPattern _pattern, float time = 0.0f);

		// 現在のボスの行動状態を取得する
		const BossPattern& getBossPattern();

		// 1つ前のボスの行動を取得する
		const BossPattern getPrevBossPattern();

		// 方角を決める
		void setDirection(Direction _dir);

	private:
		GameScene* gameScene;
		BossAction::BossOrderComponent* component;
		BossPattern bossPattern;
		BossPattern prevBossPattern;  // 1つ前のボスの行動

	public:
		bool isaaajump = false;
	};
}

#endif // !BOSS_H