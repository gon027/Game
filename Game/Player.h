#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"

using std::vector;

namespace gnGame {

	// �v���C���[�̉摜
	struct PlayerImage {
		Texture texture;
		Sprite sprite;

		PlayerImage();
		~PlayerImage() = default;
	};

	// �v���C���[�̈ړ��Ɋւ�����
	struct PlayerMoveInfo {
		PlayerMoveInfo();
		~PlayerMoveInfo() = default;

		bool isJump;         // �W�����v�ł��邩
		bool isSecondJump;   // 2��ڂ̃W�����v�ł��邩
		bool isGround;       // �n�ʂɒ��n���Ă��邩
	};

	// �v���C���[�̓����蔻��
	struct PlayerHit {
		vector<Vector2> right;
		vector<Vector2> left;
		vector<Vector2> top;
		vector<Vector2> bottom;

		PlayerHit()
			: right(2)
			, left(2)
			, top(2)
			, bottom(2)
		{}
	};
	
	// �v���C���[�{��
	class Player : public IActor{
	public:
		Player(Map& _map);
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		//void move();
		//void jump();

		void debug();

	private:
		Map map;

		PlayerImage pImage;
		Vector2 pos;          // ���W
		Vector2 velocity;     // ���x
		Bounds bounds;
		PlayerHit pHit;
		// PlayerMoveInfo pmInfo;

		bool isJump = false;
		bool isGround = false;

		// �f�o�b�O�p
		Point pt;
	};

}

#endif // !PLAYER_H
