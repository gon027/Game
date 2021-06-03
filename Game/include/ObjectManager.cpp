#include "ObjectManager.h"
#include <algorithm>

namespace gnGame {

	void ObjectManager::addObject(const ObjectPtr& _object)
	{
		objectList.emplace_back(_object);
	}

	void ObjectManager::removeObject(const ObjectPtr& _object)
	{
		auto result = std::find(objectList.begin(), objectList.end(), _object);
		objectList.erase(result);
	}

	void ObjectManager::onStart()
	{
		std::for_each(objectList.begin(), objectList.end(), [](ObjectPtr& _obj) {
			_obj->onStart();
		});
	}
	
	void ObjectManager::onUpdate()
	{
		std::for_each(objectList.begin(), objectList.end(), [](ObjectPtr& _obj) {
			_obj->onUpdate();
		});
	}

	void ObjectManager::onDraw()
	{
		std::for_each(objectList.begin(), objectList.end(), [](ObjectPtr& _obj) {

			});
	}
	
	void ObjectManager::clearList()
	{
		objectList.clear();
	}
}