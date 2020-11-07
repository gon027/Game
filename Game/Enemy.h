#ifndef ENEMY_H
#define ENEMY_H

#include "Lib.h"
#include "Actor.h"
#include "Map.h"

namespace gnGame {

	class Camera;
	class Map;

	class Enemy : public IActor {
	public:
		Enemy(Camera* _camera, Map& _map);
		~Enemy() = default;

		void onStart() override;
		void onUpdate() override;

		void setMap(Map& _map);

		void intersectTileMap();

	private:
		Camera* camera;
		Map map;

		Vector2 pos;          // ç¿ïW
		Vector2 velocity;     // ë¨ìx
		Bounds bounds;
		IntersectPoints intersectPoint;

		bool isJump = false;
		bool isGround = false;

		Texture tex;
		Sprite sp;
	};

}

#endif // !ENEMY_H