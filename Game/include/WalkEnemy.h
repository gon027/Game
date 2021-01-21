#ifndef WALKENEMY_H
#define WALKENEMY_H

#include "Enemy.h"

namespace gnGame {

	/// <summary>
	/// �����G
	/// �꒼���ɕ����Ă���
	/// </summary>
	class WalkEnemy : public Enemy{
	public:
		WalkEnemy();
		WalkEnemy(const Vector2 _pos, const ActorParameter _parameter);
		virtual ~WalkEnemy() = default;

		virtual void onStart() override;

		virtual void onUpdate() override;
	};
}

#endif // !WALKENEMY_H