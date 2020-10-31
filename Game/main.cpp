#include "Lib.h"
#include "Player.h"
#include "WindowInfo.h"
#include "Map.h"
#include "Camera.h"
using namespace gnGame;

void gnMain() {
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	Camera camera{ };
	camera.onStart();

	Map map{ &camera };
	map.loadMapFile("Map/Test_Map.txt");

	Player player{ &camera, map };
	player.onStart();

	while (app.doEvent()) {
		app.begin();

		camera.onUpdate();
		map.drawMap();
		player.onUpdate();
		

		app.end();
	}
}