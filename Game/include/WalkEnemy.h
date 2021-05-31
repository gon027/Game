#ifndef WALKENEMY_H
#define WALKENEMY_H

#include "Enemy.h"
#include "../FrameTimer.h"

namespace gnGame {

	/// <summary>
	/// �����G
	/// �꒼���ɕ����Ă���
	/// </summary>
	class WalkEnemy : public Enemy{
	public:
		WalkEnemy(const Vector2 _pos, const ActorParameter _parameter);
		virtual ~WalkEnemy() = default;

		virtual void onStart() override;

		virtual void onUpdate() override;

		void action();

	private:
		FrameTimer frameTimer;
		AnimSprite waitAnimSprite;    // �ҋ@�p�̉摜
		AnimSprite actionAnimSprite;  // �A�j���[�V�����p�̉摜
	};
}

#endif // !WALKENEMY_H