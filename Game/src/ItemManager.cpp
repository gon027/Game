#include "../include/ItemManager.h"
#include "../include/Item.h"
#include "../include/Player.h"

namespace gnGame {

    ItemManager* ItemManager::getIns()
    {
        static ItemManager Instance;
        return &Instance;
    }

    void ItemManager::addItem(ItemPtr& _item)
    {
        for (auto i{ 0 }; i < itemList.size(); ++i) {
            if (!itemList[i]) {
                itemList[i] = _item;
                return;
            }
        }

        itemList.emplace_back(_item);
    }

    void ItemManager::removeItem(size_t _index)
    {
        if (!itemList[_index]) {
            return;
        }

        itemList[_index] = nullptr;
    }

    void ItemManager::onUpdateItemList()
    {
        for (auto& item : itemList) {
            if (item) {
                item->onUpdate();
            }
        }
    }

    void ItemManager::collisionPlayer(Player& _player)
    {
        for (auto& item : itemList) {
            if (!item) {
                continue;
            }

            if (item->getCollider().isHitTest(_player.getCollider())) {
                //item->setActive(false);
                item->setEffect(_player.getPlayerBody());
                item = nullptr;
            }
        }
    }

    void ItemManager::claerList()
    {
        // ”z—ñ‚ðnullptr‚Å–„‚ß‚é
        for (size_t i{ 0 }; i < itemList.size(); ++i) {
            if (itemList[i]) {
                itemList[i] = nullptr;
            }
        }
    }

}
