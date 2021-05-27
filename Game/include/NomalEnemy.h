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
		NomalEnemy();
		NomalEnemy(const Vector2& _pos, const ActorParameter _parameter, Direction _direction);
		virtual ~NomalEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		void action();

	private:
		FrameTimer frameTime;
		AnimSprite waitAnimSprite;    //�ҋ@�p�̉摜
		AnimSprite actionAnimSprite;  // �A�j���[�V�����p�̉摜
	};
}

#endif // !NOMALENEMY_H