#ifndef PLAYER_H
#define PLAYER_H

#include "Lib.h"
#include "Actor.h"
#include "Map.h"

namespace gnGame {

	struct PlayerImage {
		Texture texture;
		Sprite sprite;

		PlayerImage();
		~PlayerImage() = default;
	};
	
	class Player : public IActor{
	public:
		Player(Map& _map);
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		void debug();

	private:
		Map map;

		PlayerImage pImage;
		Vector2 pos;
		Vector2 velocity;
		Bounds bounds;

		bool isJump = false;
		bool isGround = false;
	};

}

#endif // !PLAYER_H
