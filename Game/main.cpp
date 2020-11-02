#include "Lib.h"
#include "Player.h"
#include "WindowInfo.h"
#include "Map.h"
#include "Camera.h"
using namespace gnGame;

void gnMain() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	Camera camera{ };
	camera.onStart();

	Map map{ &camera };
	map.loadMapFile("Map/Test_Map.txt");

	Player player{ &camera, map };
	player.onStart();

	while (app.doEvent()) {
		app.begin();

		
		map.drawMap();
		player.onUpdate();
		camera.onUpdate();
		
		app.end();
	}
}