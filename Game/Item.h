#ifndef ITEM_H
#define ITEM_H

#include "gnLib.h"

namespace gnGame {

	class Player;

	/*
	・アイテム考案
	・回復
	・攻撃力UP
	・守備力UP
	・速度UP
	*/

	class Item : public Object {
	public:
		Item();
		virtual ~Item() = default;

		void onStart();

		void onUpdate();

		bool isOnScreen();

		// プレイヤーにアイテム効果を渡す
		void setEffect(Player& _player);

		// コライダーを取得
		BoxCollider& getCollider();

	private:
		Sprite sprite;
		BoxCollider collider;
	};

}

#endif // !ITEM_H
