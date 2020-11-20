#include "../include/Game.h"
#include "../include/WindowInfo.h"
#include "../include/EnemyManager.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"
#include <memory>

namespace gnGame {

    Game::Game()
        : map(new Map())
        , player()
        , enemy(new Enemy({100.f, 200.f}))
        , fps()
        , bg(Vector2{WindowInfo::WindowWidth / 2.0f, WindowInfo::WindowHeight / 2.0f})
    {
    }

    Game::~Game()
    {
        delete map;
    }

    void Game::onStart()
    {
        //bg.setTexture();
        map->loadMapFile("Asset/MapData/Test_Map.txt");
        player.onStart();
        player.setMap(*map);
        //enemy->onStart();
        //enemy->setMap(*map);

        for(int i = 0; i < 5; ++i) {
            auto e = std::make_shared<Enemy>();
            e->transform.setPos(400.f + 20.f * i, 500.0f);
            e->setMap(*map);
            e->onStart();
            EnemyManager::getIns()->addActor(e);
        }
        
    }

    void Game::onUpdate(float _deltaTime)
    {
        fps.onUpdate();

        {
            //bg.draw();
            map->drawMap();
            player.onUpdate();
            //enemy->onUpdate();

            EnemyManager::getIns()->onUpdateActorList();
            EnemyManager::getIns()->collisionPlayer(player);

            BulletManager::getIns()->onUpdateBulletList();
            BulletManager::getIns()->collisionMap(*map);
            BulletManager::getIns()->collisionActor(player);

            fps.drawFps();
        }

        fps.wait();
    }

    void Game::onFinal()
    {

    }
}