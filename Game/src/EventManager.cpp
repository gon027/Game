#include "../include/EventManager.h"
#include "../include/EventObject.h"
#include "../include/Player.h"

namespace gnGame {

    EventManager* EventManager::getIns()
    {
        static EventManager Instance;
        return &Instance;
    }

    void EventManager::addEvent(EventPtr& _event)
    {
        eventList.emplace_back(_event);
    }

    void EventManager::removeEvent(EventPtr& _event)
    {
        
    }

    void EventManager::onUpdateEventList()
    {
        for (auto& e : eventList) {
            if (!e) {
                continue;
            }

            e->onUpdate();
        }
    }

    void EventManager::collisionPlayer(Player& _player)
    {
        for (auto& e : eventList) {
            if (!e) {
                continue;
            }

            if (e->getCollider().isHitTest(_player.getCollider())) {
                e->onEvent();
                break;
            }
        }
    }

    void EventManager::claerList()
    {
        eventList.clear();
    }

}
