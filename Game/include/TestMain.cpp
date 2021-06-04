#include "TestMain.h"

#include "Lib.h"

namespace test {

	TestPlayer::TestPlayer(int _value)
		: value(_value)
	{

	}

	void TestPlayer::testUpdate() {
		if (Input::getKeyDown(Key::A)) {
			auto e{ new TestEnemy{100} };
			TestManager::getIns()->addTest(e);
		}
	}

	TestEnemy::TestEnemy(int _value)
		: value(_value)
	{

	}

	void TestEnemy::testUpdate() {
		++value;
	}

	void TestManager::addTest(TestObjectPtr _obj) {
		objectList.push_back(_obj);
	}

	void TestManager::updateTest()
	{
		std::for_each(objectList.begin(), objectList.end(), [](TestObjectPtr _obj) {
			_obj->testUpdate();
		});
	}

	void TestManager::finalTest()
	{
		std::for_each(objectList.begin(), objectList.end(), [](TestObjectPtr _obj) {
			if (_obj) {
				delete _obj;
				_obj = nullptr;
			}
		});

		objectList.clear();
	}

	TestMain::TestMain()
		: player(new TestPlayer{ 100 })
	{
		TestManager::getIns()->addTest(player);
	}

	TestMain::~TestMain()
	{
		TestManager::getIns()->finalTest();
	}

	void TestMain::run()
	{
		TestManager::getIns()->updateTest();

		if (Input::getKeyDown(Key::Z)) {
			auto e{ new TestEnemy{100} };
			TestManager::getIns()->addTest(e);
		}

		gnLib::Debug::drawFormatText(0, 0, gnLib::Color::Red, "size = %d", TestManager::getIns()->getSize());
	}

}