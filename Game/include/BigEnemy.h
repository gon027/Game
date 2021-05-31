#ifndef BIGENEMY_H
#define BIGENEMY_H

#include "Enemy.h"
#include "FrameTimer.h"

namespace gnGame {

	/// <summary>
	/// 大きい敵
	/// </summary>
	class BigEnemy : public Enemy {
	public:
		BigEnemy(const Vector2& _pos, const ActorParameter _parameter);
		virtual ~BigEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		void action();

	private:
		FrameTimer frameTime;
		AnimSprite waitAnimSprite;    //待機用の画像
		AnimSprite actionAnimSprite;  // アニメーション用の画像
	};
}

#endif // !BIGENEMY_H