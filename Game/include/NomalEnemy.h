#ifndef NOMALENEMY_H
#define NOMALENEMY_H

#include "Enemy.h"
#include "EnemyState.h"
#include "FrameTimer.h"

namespace gnGame {

	/// <summary>
	/// 普通の敵
	/// 歩いて、弾を撃ってくる
	/// </summary>
	class NomalEnemy : public Enemy {
	public:
		NomalEnemy();
		NomalEnemy(const Vector2& _pos, const ActorParameter _parameter, Direction _direction);
		virtual ~NomalEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		void action();

	private:
		FrameTimer frameTime;
		AnimSprite waitAnimSprite;    //待機用の画像
		AnimSprite actionAnimSprite;  // アニメーション用の画像
	};
}

#endif // !NOMALENEMY_H