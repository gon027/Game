#include "Lib.h"
#include "Player.h"
#include "WindowInfo.h"
#include "Map.h"
using namespace gnGame;

void gnMain() {
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	Map map;
	map.loadMapFile("Map/Test_Map.txt");

	Player player{ map };
	player.onStart();

	while (app.doEvent()) {
		app.begin();

		map.drawMap();
		player.onUpdate();

		app.end();
	}
}