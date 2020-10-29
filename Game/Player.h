#ifndef PLAYER_H
#define PLAYER_H

#include "Lib.h"
#include "Actor.h"

namespace gnGame {

	struct PlayerImage {
		Texture texture;
		Sprite sprite;

		PlayerImage();
		~PlayerImage() = default;
	};
	
	class Player : public IActor{
	public:
		Player();
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		void debug();

	private:
		PlayerImage pImage;
		Vector2 pos;
		Vector2 velocity;
		Bounds bounds;

		bool isJump = false;
		bool isGround = false;
	};

}

#endif // !PLAYER_H
