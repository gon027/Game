#ifndef WALKENEMY_H
#define WALKENEMY_H

#include "Enemy.h"
#include "../FrameTimer.h"

namespace gnGame {

	/// <summary>
	/// 歩く敵
	/// 一直線に歩いていく
	/// </summary>
	class WalkEnemy : public Enemy{
	public:
		WalkEnemy(const Vector2 _pos, const ActorParameter _parameter);
		virtual ~WalkEnemy() = default;

		virtual void onStart() override;

		virtual void onUpdate() override;

		void action();

	private:
		FrameTimer frameTimer;
		AnimSprite waitAnimSprite;    // 待機用の画像
		AnimSprite actionAnimSprite;  // アニメーション用の画像
	};
}

#endif // !WALKENEMY_H