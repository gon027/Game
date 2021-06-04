#include "../include/ActorManager.h"
#include "../include/Actor.h"
#include <algorithm>

namespace gnGame {

	void ActorManager::addActor(const ActorPtr& _actor)
	{
		actorList.emplace_back(_actor);
	}

	void ActorManager::onUpdate()
	{
		std::for_each(actorList.begin(), actorList.end(), [](ActorPtr& _actor) {
			if (!_actor->getActive()) {
				return;
			}

			_actor->onUpdate();
		});
	}

	void ActorManager::onDraw()
	{
		std::for_each(actorList.begin(), actorList.end(), [](ActorPtr& _actor) {
			if (!_actor->getActive()) {
				return;
			}

			_actor->onDraw();
		});	
	}

	void ActorManager::claerList()
	{
		actorList.clear();
	}

}