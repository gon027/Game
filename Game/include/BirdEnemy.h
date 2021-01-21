#ifndef BIRDENEMY_H
#define BIRDENEMY_H

#include "Enemy.h"
#include "EnemyState.h"

namespace gnGame {

	/// <summary>
	/// ‹ó‚ð”ò‚ñ‚Å‚¢‚é“G
	/// </summary>
	class BirdEnemy : public Enemy {
	public:
		BirdEnemy();
		BirdEnemy(const Vector2& _pos, const ActorParameter _parameter);
		virtual ~BirdEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;
	};
}

#endif // !BIRDENEMY_H