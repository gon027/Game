#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Lib.h"
#include "GameObject.h"
#include "Singleton.h"

namespace gnGame {

	using ObjectPtr = std::shared_ptr<GameObject>;
	using ObjectList = std::vector<ObjectPtr>;

	class ObjectManager final : public Singleton<ObjectManager> {
		friend Singleton<ObjectManager>;
	
	public:
		void addObject(const ObjectPtr& _object);

		template<class T>
		void createObject(const Vector2& _pos) {
			T* obj{ new T(_pos) };
			obj->onStart();
			objectList.emplace_back(obj);
		}

		void removeObject(const ObjectPtr& _object);

		void onStart();

		void onUpdate();

		void onDraw();

		void onFinal();

		void clearList();

		size_t getListSize() const {
			return objectList.size();
		}

	private:
		ObjectManager() 
			: objectList()
		{ }

	private:
		ObjectList objectList;
	};

}

#endif // !OBJECTMANAGER_H