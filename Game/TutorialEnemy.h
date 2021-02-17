#ifndef TUTORIALENEMY_H
#define TUTORIALENEMY_H

#include "include/Enemy.h"

namespace gnGame {

	// 1-3で登場する動かないチュートリアル用の敵

	class TutorialEnemy : public Enemy{
	public:
		TutorialEnemy(const Vector2 _pos);
		~TutorialEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

	private:
		AnimSprite waitAnim;
	};

}

#endif // !TUTORIALENEMY_H
