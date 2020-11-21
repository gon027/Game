#ifndef ITEM_H
#define ITEM_H

#include "gnLib.h"

namespace gnGame {

	class Player;

	/*
	�E�A�C�e���l��
	�E��
	�E�U����UP
	�E�����UP
	�E���xUP
	*/

	class Item : public Object {
	public:
		Item();
		virtual ~Item() = default;

		void onStart();

		void onUpdate();

		bool isOnScreen();

		// �v���C���[�ɃA�C�e�����ʂ�n��
		void setEffect(Player& _player);

		// �R���C�_�[���擾
		BoxCollider& getCollider();

	private:
		Sprite sprite;
		BoxCollider collider;
	};

}

#endif // !ITEM_H
