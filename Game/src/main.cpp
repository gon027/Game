#include "../include/Main.h"

namespace Static {
	static constexpr int N = 60;
	static constexpr int FPS = 60;
}

class Fps {
public:
	Fps() 
		: startTime(0)
		, count(0)
		, fps(0)
	{}

	bool onUpdate() {
		if (count == 0) {
			startTime = Time::getTime();
		}

		if (count == Static::N) {
			int t = Time::getTime();
			fps = 1000.0f / ((t - startTime) / (float)Static::N);
			count = 0;
			startTime = t;
		}

		count++;
		return true;
	}

	void wait() {
		int tookTime = Time::getTime() - startTime;
		int waitTime = count * 1000 / Static::FPS - tookTime;
		if (waitTime > 0) {
			Sleep(waitTime);
		}
	}

	void draw() {
		Debug::drawFormatText(0, 20, Color::Black, "Fps = %.1f", fps);
	}

private:
	int startTime{ 0 };
	int count{ 0 };
	float fps{ 0.0f };

};



void gnMain() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	Game gameScene;
	gameScene.onStart();

	Fps f;

	while (app.doEvent()) {
		app.begin();

		f.onUpdate();
		f.draw();

		Debug::drawFormatText(0, 0, Color::Black, "%lf", Time::deltaTime());

		gameScene.onUpdate(Time::deltaTime());

		f.wait();

		app.end();
	}

	gameScene.onFinal();
}