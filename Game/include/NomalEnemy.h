#ifndef NOMALENEMY_H
#define NOMALENEMY_H

#include "Enemy.h"
#include "EnemyState.h"

namespace gnGame {

	/// <summary>
	/// •’Ê‚Ì“G
	/// •à‚¢‚ÄA’e‚ğŒ‚‚Á‚Ä‚­‚é
	/// </summary>
	class NomalEnemy : public Enemy {
	public:
		NomalEnemy();
		NomalEnemy(const Vector2& _pos, const ActorParameter _parameter);
		virtual ~NomalEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;
	};
}

#endif // !NOMALENEMY_H