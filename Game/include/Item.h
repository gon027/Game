#ifndef ITEM_H
#define ITEM_H

#include "Lib.h"

namespace gnGame {

	class Player;
	class PlayerBody;

	// アイテムの種類
	enum class ItemType {
		HP,        // HPを回復
		MP,        // MPを回復
		Attack,    // 攻撃力を上げる
		Defence,   // 守備力を上げる
		Speed,     // 速度を上げる
	};

	/// <summary>
	/// アイテムクラス
	/// </summary>
	class Item : public Object {
	public:
		Item(ItemType _itemType);
		~Item() = default;

		void onStart();

		void onUpdate();

		bool isOnScreen();

		// プレイヤーにアイテム効果を渡す
		void setEffect(PlayerBody& _player);

		// コライダーを取得
		BoxCollider& getCollider();

		// アイテムの種類を取得
		const ItemType getItemType();

	private:
		Sprite sprite;
		BoxCollider collider;
		ItemType itemType;
	};

}

#endif // !ITEM_H
