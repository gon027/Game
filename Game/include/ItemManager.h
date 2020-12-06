#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <vector>
#include <memory>

namespace gnGame {

	namespace {
		// �ő�̐�
		constexpr int MaxItemListSize = 1;
	}

	class Item;
	class Player;

	using ItemPtr = std::shared_ptr<Item>;
	using ItemList = std::vector<ItemPtr>;

	class ItemManager {
	public:
		static ItemManager* getIns();

	public:
		// �A�C�e����ǉ�
		void addItem(ItemPtr& _item);

		// �A�C�e�����폜
		void removeItem(size_t _index);

		// �X�V
		void onUpdateItemList();

		// �v���C���[�Ƃ̓����蔻��
		void collisionPlayer(Player& _player);

		// �z�����ɂ���
		void claerList();

		// ���X�g�̃T�C�Y���擾
		size_t getListSize() {
			return itemList.size();
		}

	private:
		ItemManager() : itemList(MaxItemListSize) {};
		ItemManager(const ItemManager&);
		ItemManager& operator= (const ItemManager&);

	private:
		ItemList itemList;
	};

}

#endif // !ITEMMANAGER_H
