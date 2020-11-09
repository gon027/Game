#include "Main.h"

void gnMain() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	Game gameScene;
	gameScene.onStart();

	Time time;

	while (app.doEvent()) {
		app.begin();
		time.beginTime();

		gameScene.onUpdate();

		Debug::drawFormatText(0, 0, Color::Black, "%d", time.deltaTime());

		time.endTime();
		app.end();
	}
}