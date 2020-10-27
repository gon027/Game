#pragma comment(lib, "Game2DProject.lib")
#include "gnLib.h"

void gnMain() {
	App app;

	Rect r;

	while (app.doEvent()) {
		app.begin();

		if (Input::getLeftButton()) {
			break;
		}

		r.setSize(100, 100);
		r.setPos(300.f, 300.f);
		r.setColor(Color::Blue);
		r.draw();

		app.end();
	}
}