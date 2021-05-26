#ifndef COIN_H
#define COIN_H

#include "Item.h"

namespace gnGame {

	class Coin : public Item {
	public:
		Coin(const Vector2& _pos);
		~Coin() = default;

		void onStart() override;

		void onUpdate() override;

		// �v���C���[�ɃA�C�e�����ʂ�n��
		void onCollision(class Player& _player) override;

		// �R���C�_�[���擾
		ICollider& getCollider() override;

	public:
		CircleCollider collider;
	};
}

#endif // !COIN_H