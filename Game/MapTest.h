#pragma once

#include <vector>
#include <string>
#include "include/Lib.h"
#include "include/Map.h"
#include "include/Player.h"

class MapTest {
public:
	MapTest()
		: gameMap()
		, pos()
		, mapTest(4)
		, p()
	{
		mapTest[0] = "TestMap_01.txt";
		mapTest[1] = "TestMap_02.txt";
		mapTest[2] = "TestMap_03.txt";
		mapTest[3] = "TestMap_04.txt";
	}

	~MapTest() = default;

	void start() {
		gameMap.loadMapFile("Asset/MapData/" + mapTest[current]);
		Camera::setMapInfo(gameMap.getMapSize());
		p.onStart();
		p.setMap(&gameMap);
		p.transform.pos.setPos(100, 50);
	}

	void update() {
		gameMap.drawMap();
		p.onUpdate();

		//Camera::setTarget(pos);
		//Debug::drawFormatText(300, 300, Color::Black, "%d", current);
		//Debug::drawFormatText(300, 330, Color::Black, "%s", gameMap.getMapSize().toString().c_str());
		//Debug::drawFormatText(300, 360, Color::Black, "%s", s.toString().c_str());

		/*
		if (Input::getKey(Key::LEFT)) {
			pos.x -= 2.0f;
		}

		if (Input::getKey(Key::RIGHT)) {
			pos.x += 2.0f;
		}

		if (Input::getKey(Key::UP)) {
			pos.y -= 2.0f;
		}

		if (Input::getKey(Key::DOWN)) {
			pos.y += 2.0f;
		}
		*/

		if (Input::getKeyDown(Key::K)) {
			current = (current + 1) % 4;
			gameMap.claerMap();
			gameMap.loadMapFile("Asset/MapData/" + mapTest[current]);
			Camera::setMapInfo(gameMap.getMapSize());
			p.transform.setPos(100, 50);
		}

	}


private:
	int current = 0;
	gnGame::Map gameMap;
	Vector2 pos;
	std::vector<std::string> mapTest;
	Player p;
};