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

		// Actor‚ğ“®‚©‚·
		virtual void moveActor() = 0;

		// ŠO•”‚©‚ç‰Á‘¬“x‚ğ‰ÁZ‚µ‚½‚¢‚Æ‚«‚ÉŒÄ‚Ño‚·
		//virtual void addVelocity(const Vector2& _velocity);

	protected:
		Vector2 velocity;
	};

}

#endif // !ACTORMOVE_H
