#ifndef ACTOAMANAGER_H
#define ACTOAMANAGER_H

#include "Lib.h"
#include "Singleton.h"
#include <vector>
#include <memory>

namespace gnGame {

	class Actor;
	using ActorPtr = std::shared_ptr<Actor>;  // 敵のポインタ
	using ActorList = std::vector<ActorPtr>;  // 敵のポインタのリスト

	class ActorManager : public Singleton<ActorManager> {
		friend Singleton<ActorManager>;

	public:
		template<class A, typename ...Args>
		void createActor(const Vector2& _pos = Vector2::Zero) {
			//ActorPtr actor{ new A{ _pos, Args ...args} };
			//actor->onStart();
			//actorList.emplace_back(actor);
		}

		void addActor(const ActorPtr& _actor);

		// void removeActor();

		void onUpdate();

		void onDraw();

		void claerList();

		inline size_t getListSize() {
			return actorList.size();
		}

	private:
		ActorManager()
			: actorList()
		{}

	private:
		ActorList actorList;
	};

}

#endif // !ACTOAMANAGER_H
