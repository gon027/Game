#ifndef TUTORIALENEMY_H
#define TUTORIALENEMY_H

#include "include/Enemy.h"

namespace gnGame {

	// 1-3�œo�ꂷ�铮���Ȃ��`���[�g���A���p�̓G

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
