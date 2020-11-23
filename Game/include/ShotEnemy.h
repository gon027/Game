#ifndef SHOTENEMY_H
#define SHOTENEMY_H

#include "Enemy.h"

namespace gnGame {

	/// <summary>
	/// ’e‚ð•ú‚Â“G
	/// </summary>
	class ShotEnemy : public Enemy {
	public:
		ShotEnemy();
		ShotEnemy(const Vector2& _pos);
		virtual ~ShotEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

	private:
		void shot();

	private:
		float shotTime;
	};

}

#endif // !SHOTENEMY_H