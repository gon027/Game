#pragma once

#include "Singleton.h"
#include <algorithm>
#include <vector>
#include <memory>

namespace test {

	class TestBaseObject {
	public:
		~TestBaseObject() = default;

		virtual void testUpdate() = 0;
	};

	class TestPlayer : public TestBaseObject{
	public:
		TestPlayer(int _value);

		void testUpdate() override;

	public:
		int value;
	};

	class TestEnemy : public TestBaseObject {
	public:
		TestEnemy(int _value);

		void testUpdate() override;

	public:
		int value;
	};

	using TestObjectPtr = TestBaseObject*;
	using TestObjectList = std::vector<TestObjectPtr>;

	class TestManager : public gnGame::Singleton<TestManager> {
		friend gnGame::Singleton<TestManager>;

	public:
		void addTest(TestObjectPtr _obj);

		void updateTest();

		void finalTest();

		inline size_t getSize() {
			return objectList.size();
		}

	private:
		TestObjectList objectList;
	};

	class TestMain {
	public:
		TestMain();
		~TestMain();

		void run();

	private:
		TestPlayer* player;
	};

}