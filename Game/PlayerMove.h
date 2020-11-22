#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

#include "ActorMove.h"

namespace gnGame {

	class Player;

	class PlayerMove : public ActorMove {
	public:
		PlayerMove(Player* _player);
		~PlayerMove() = default;

		void moveActor() override;

	private:
		void movePlayer();

	};

}

#endif // !PLAYERMOVE_H