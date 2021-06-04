#ifndef NOMALENEMY_H
#define NOMALENEMY_H

#include "Enemy.h"
#include "EnemyState.h"
#include "FrameTimer.h"

namespace gnGame {

	/// <summary>
	/// ���ʂ̓G
	/// �����āA�e�������Ă���
	/// </summary>
	class NomalEnemy : public Enemy {
	public:
		NomalEnemy(const Vector2& _pos, const ActorParameter _parameter, Direction _direction);
		virtual ~NomalEnemy() = default;

		void onStart() override;
		void onUpdate() override;
		void onDraw() override;

		void action();

	private:
		FrameTimer frameTime;
		AnimSprite waitAnimSprite;    //�ҋ@�p�̉摜
		AnimSprite actionAnimSprite;  // �A�j���[�V�����p�̉摜
	};
}

#endif // !NOMALENEMY_H