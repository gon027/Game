#include "Lib.h"
#include "Player.h"
#include "WindowInfo.h"
#include "Map.h"
#include <vector>
#include <fstream>
#include <string>
using namespace gnGame;
using std::vector;

void gnMain() {
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	Player player;
	player.onStart();

	Map map;
	map.loadMapFile("Map/Test_Map.txt");

	while (app.doEvent()) {
		app.begin();

		map.drawMap();
		player.onUpdate();

		app.end();
	}
}