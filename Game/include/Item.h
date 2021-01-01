#ifndef ITEM_H
#define ITEM_H

#include "Lib.h"

namespace gnGame {

	class Player;
	class PlayerBody;

	// �A�C�e���̎��
	enum class ItemType {
		HP,        // HP����
		MP,        // MP����
		Attack,    // �U���͂��グ��
		Defence,   // ����͂��グ��
		Speed,     // ���x���グ��
	};

	/// <summary>
	/// �A�C�e���N���X
	/// </summary>
	class Item : public Object {
	public:
		Item(ItemType _itemType);
		~Item() = default;

		void onStart();

		void onUpdate();

		bool isOnScreen();

		// �v���C���[�ɃA�C�e�����ʂ�n��
		void setEffect(PlayerBody& _player);

		// �R���C�_�[���擾
		BoxCollider& getCollider();

		// �A�C�e���̎�ނ��擾
		const ItemType getItemType();

	private:
		Sprite sprite;
		BoxCollider collider;
		ItemType itemType;
	};

}

#endif // !ITEM_H
