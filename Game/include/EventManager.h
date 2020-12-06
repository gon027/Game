#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <memory>
#include "gnLib.h"

namespace gnGame {

	namespace {
		// �ő�̐�
		constexpr int EventMaxSize = 1;
	}

	class Player;
	class EventObject;

	using EventPtr = std::shared_ptr<EventObject>;   // �G�̃|�C���^
	using EventList = std::vector<EventPtr>;         // �C�x���g�̃|�C���^�̃��X�g

	class EventManager {
	public:
		static EventManager* getIns();

	public:
		~EventManager() = default;

		// �e��ǉ�
		void addEvent(EventPtr& _event);

		// �e���폜
		void removeEvent(EventPtr& _event);

		// Update�֐����Ăяo��
		void onUpdateEventList();

		// �G�Ƃ̏Փ˔���
		void collisionPlayer(Player& _event);

		// �z�����ɂ���
		void claerList();

		// ���X�g�̃T�C�Y���擾����
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
