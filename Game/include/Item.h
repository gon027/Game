#ifndef ITEM_H
#define ITEM_H

#include "Lib.h"
#include "GameObject.h"

namespace gnGame {

	/// <summary>
	/// アイテムのインターフェース
	/// </summary>
	class Item : public GameObject {
	public:
		Item()
			: sprite() 
		{ }

		~Item() = default;

		// プレイヤーにアイテム効果を渡す
		virtual void onCollision(class Player& _player) = 0;

		// コライダーを取得
		virtual ICollider& getCollider() = 0;

	protected:
		Sprite sprite;
	};

}

#endif // !ITEM_H
