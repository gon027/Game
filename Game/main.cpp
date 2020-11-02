#include "Main.h"

void gnMain() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	Game gameScene;
	gameScene.onStart();

	while (app.doEvent()) {
		app.begin();

		gameScene.onUpdate();
		
		app.end();
	}
}