#include "../include/Game.h"
#include "../include/WindowInfo.h"
#include "../include/EnemyManager.h"
#include "../include/TextureManager.h"
#include "../BulletManager.h"
#include <memory>

namespace gnGame {

    Game::Game()
        : map(new Map())
        , player()
        , enemy({100.f, 200.f})
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
        map->loadMapFile("Asset/MapData/MapTest03.txt");
        player.onStart();
        player.setMap(*map);
        enemy.onStart();
        enemy.setMap(*map);

        /*
        auto e = std::make_shared<Enemy>();
        e->transform.setPos(200.f, 300.0f);
        EnemyManager::getIns()->addActor(e);

        EnemyManager::getIns()->onStartEnemyList();
        EnemyManager::getIns()->setMap(*map);
        */
    }

    void Game::onUpdate(float _deltaTime)
    {
        fps.onUpdate();

        {
            //bg.draw();
            map->drawMap();
            player.onUpdate(_deltaTime);
            enemy.onUpdate(0.f);
            //EnemyManager::getIns()->onUpdateActorList();

            /*if (Input::getKeyDown(Key::J)) {
                auto e = std::make_shared<Enemy>();
                e->transform.setPos(100.f, 300.0f);
                e->setMap(*map);
                e->onStart();
                EnemyManager::getIns()->addActor(e);
            }
            */

            BulletManager::getIns()->onUpdateBulletList();

            fps.drawFps();
        }

        fps.wait();
    }

    void Game::onFinal()
    {
        CameraIns->destroy();
    }
}