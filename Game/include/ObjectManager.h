#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Lib.h"
#include "GameObject.h"
#include "Singleton.h"

namespace gnGame {

	using ObjectPtr = GameObject*;
	using ObjectList = std::vector<ObjectPtr>;

	class ObjectManager final : public Singleton<ObjectManager> {
		friend Singleton<ObjectManager>;
	
	public:
		void addObject(const ObjectPtr& _object);

		void removeObject(const ObjectPtr& _object);

		void onStart();

		void onUpdate();

		void onDraw();

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