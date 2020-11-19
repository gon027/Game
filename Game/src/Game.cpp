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
        map->loadMapFile("Asset/MapData/MapTest03.txt");
        player.onStart();
        player.setMap(*map);
        enemy->onStart();
        enemy->setMap(*map);

        EnemyManager::getIns()->onStartEnemyList();
        EnemyManager::getIns()->setMap(*map);
        
    }

    void Game::onUpdate(float _deltaTime)
    {
        fps.onUpdate();

        {
            //bg.draw();
            map->drawMap();
            player.onUpdate();
            enemy->onUpdate();

            if (enemy->getCollider().isHitTest(player.getCollider())) {
                player.setActive(false);
            }


            EnemyManager::getIns()->onUpdateActorList();
            EnemyManager::getIns()->collisionPlayer(player);

            
            if (Input::getKeyDown(Key::J)) {
                auto e = std::make_shared<Enemy>();
                e->transform.setPos(100.f, 300.0f);
                e->setMap(*map);
                e->onStart();
                EnemyManager::getIns()->addActor(e);
            }
            

            BulletManager::getIns()->onUpdateBulletList();
            BulletManager::getIns()->collisionActor(enemy);
            BulletManager::getIns()->collisionMap(*map);

            fps.drawFps();
        }

        fps.wait();
    }

    void Game::onFinal()
    {
        CameraIns->destroy();
    }
}