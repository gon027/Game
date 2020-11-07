#include "Main.h"

void gnMain() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	//Game gameScene;
	//gameScene.onStart();

	Texture mapData("Image/MapData.png");
	Sprite md{ mapData };
	auto sprit = Texture::spriteTexture(mapData, 20, 20);


	while (app.doEvent()) {
		app.begin();

		//gameScene.onUpdate();

		//md.setPos(400, 400);
		//md.draw();

		//md.setPos(400, 400);
		//md.draw(sprit[0]);

		md.setPos(430, 400);
		md.draw(sprit[0]);

		md.setPos(460, 400);
		md.draw(sprit[0]);

		md.setPos(490, 400);
		md.draw(sprit[1]);

		md.setPos(520, 400);
		md.draw(sprit[1]);

		md.setPos(550, 400);
		md.draw(sprit[1]);
		
		md.setPos(430, 430);
		md.draw(sprit[0]);

		md.setPos(460, 430);
		md.draw(sprit[0]);

		md.setPos(490, 430);
		md.draw(sprit[1]);

		md.setPos(520, 430);
		md.draw(sprit[1]);

		md.setPos(550, 430);
		md.draw(sprit[1]);



		app.end();
	}
}