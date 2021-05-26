#ifndef ITEM_H
#define ITEM_H

#include "Lib.h"

namespace gnGame {

	/// <summary>
	/// �A�C�e���̃C���^�[�t�F�[�X
	/// </summary>
	class Item : public Object {
	public:
		Item();
		~Item() = default;

		virtual void onStart();

		virtual void onUpdate();

		// �v���C���[�ɃA�C�e�����ʂ�n��
		virtual void onCollision(class Player& _player) = 0;

		// �R���C�_�[���擾
		virtual ICollider& getCollider() = 0;

	protected:
		Sprite sprite;
	};

}

#endif // !ITEM_H
