#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <memory>
#include "gnLib.h"

namespace gnGame {

	namespace {
		// 最大の数
		constexpr int EventMaxSize = 1;
	}

	class Player;
	class EventObject;

	using EventPtr = std::shared_ptr<EventObject>;   // 敵のポインタ
	using EventList = std::vector<EventPtr>;         // イベントのポインタのリスト

	class EventManager {
	public:
		static EventManager* getIns();

	public:
		~EventManager() = default;

		// 弾を追加
		void addEvent(EventPtr& _event);

		// 弾を削除
		void removeEvent(EventPtr& _event);

		// Update関数を呼び出す
		void onUpdateEventList();

		// 敵との衝突判定
		void collisionPlayer(Player& _event);

		// 配列を空にする
		void claerList();

		// リストのサイズを取得する
		size_t getListSize() {
			return eventList.size();
		}

	private:
		EventManager() : eventList(EventMaxSize) {};
		EventManager(const EventManager&);
		EventManager& operator= (const EventManager&);

	private:
		EventList eventList;
	};

}

#endif // !EVENTMANAGER_H
