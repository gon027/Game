#ifndef BIGENEMY_H
#define BIGENEMY_H

#include "Enemy.h"

namespace gnGame {

	/// <summary>
	/// ‘å‚«‚¢“G
	/// </summary>
	class BigEnemy : public Enemy {
	public:
		BigEnemy();
		BigEnemy(const Vector2& _pos);
		virtual ~BigEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;
	};
}


#endif // !BIGENEMY_H
