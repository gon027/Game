#ifndef BIGENEMY_H
#define BIGENEMY_H

#include "Enemy.h"
#include "FrameTimer.h"

namespace gnGame {

	/// <summary>
	/// �傫���G
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
		AnimSprite waitAnimSprite;    //�ҋ@�p�̉摜
		AnimSprite actionAnimSprite;  // �A�j���[�V�����p�̉摜
	};
}

#endif // !BIGENEMY_H