#ifndef WALKENEMY_H
#define WALKENEMY_H

#include "Enemy.h"

namespace gnGame {

	/// <summary>
	/// •à‚­“G
	/// </summary>
	class WalkEnemy : public Enemy{
	public:
		WalkEnemy();
		virtual ~WalkEnemy() = default;

		virtual void onStart() override;

		virtual void onUpdate() override;

	private:
		void walk();

	};
}

#endif // !WALKENEMY_H