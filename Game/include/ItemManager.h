#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <vector>
#include <memory>

namespace gnGame {

	namespace {
		// 最大の数
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
		// アイテムを追加
		void addItem(ItemPtr& _item);

		// アイテムを削除
		void removeItem(size_t _index);

		// 更新
		void onUpdateItemList();

		// プレイヤーとの当たり判定
		void collisionPlayer(Player& _player);

		// 配列を空にする
		void claerList();

		// リストのサイズを取得
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
