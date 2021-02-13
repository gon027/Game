#ifndef BIGENEMY_H
#define BIGENEMY_H

#include "Enemy.h"
#include "FrameTimer.h"

namespace gnGame {

	/// <summary>
	/// ‘å‚«‚¢“G
	/// </summary>
	class BigEnemy : public Enemy {
	public:
		BigEnemy();
		BigEnemy(const Vector2& _pos, const ActorParameter _parameter);
		virtual ~BigEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		void action();

	private:
		FrameTimer frameTime;
	};
}

#endif // !BIGENEMY_H