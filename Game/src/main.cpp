#include "../include/Main.h"

void gnMain() {
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	Game gameScene;
	gameScene.onStart();

	while (app.doEvent()) {
		app.begin();

		{
			Debug::drawFormatText(35, 32, Color::Black, "DeltaTime = %lf", Time::deltaTime());
			gameScene.onUpdate(Time::deltaTime());
		}

		app.end();
	}

	gameScene.onFinal();
}