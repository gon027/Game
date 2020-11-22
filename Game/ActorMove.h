#ifndef ACTORMOVE_H
#define ACTORMOVE_H

namespace gnGame {

	class Actor;

	class ActorMove {
	public:
		virtual ~ActorMove() = default;
		virtual void moveActor() = 0;

	private:
		Actor* actor;
	};

}

#endif // !ACTORMOVE_H
