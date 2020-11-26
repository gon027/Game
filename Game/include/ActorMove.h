#ifndef ACTORMOVE_H
#define ACTORMOVE_H

namespace gnGame {

	class Actor;

	class ActorMove {
	public:
		ActorMove()
			: velocity()
		{}

		virtual ~ActorMove() = default;

		// Actor�𓮂���
		virtual void moveActor() = 0;

		// �O����������x�����Z�������Ƃ��ɌĂяo��
		//virtual void addVelocity(const Vector2& _velocity);

	protected:
		Vector2 velocity;
	};

}

#endif // !ACTORMOVE_H
