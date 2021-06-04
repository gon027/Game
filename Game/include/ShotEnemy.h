#ifndef SHOTENEMY_H
#define SHOTENEMY_H

#include "Enemy.h"
#include "EnemyState.h"
#include "FrameTimer.h"

namespace gnGame {

	/// <summary>
	/// ’e‚ğ•ú‚Â“G
	/// ‚»‚Ìê‚©‚ç“®‚©‚¸’e‚ğ•ú‚Â
	/// </summary>
	class ShotEnemy : public Enemy {
	public:
		ShotEnemy(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter, Direction _direction);
		virtual ~ShotEnemy() = default;

		void onStart() override;
		void onUpdate() override;
		void onDraw() override;

		void action();

	private:
		GameScene* gameScene;
		AnimSprite waitAnimSprite;    // ‘Ò‹@—p‚Ì‰æ‘œ
		EnemyState::Attack::EnemyAttack enemyAttack;
	};

}

#endif // !SHOTENEMY_H