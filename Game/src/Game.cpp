#include "../include/Game.h"
#include "../include/WindowInfo.h"
#include "../include/EnemyManager.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"
#include "../ItemManager.h"
#include <memory>

namespace gnGame {

    Game::Game()
        : map(new Map())
        , player()
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
        bg.setTexture();
        map->loadMapFile("Asset/MapData/MapTest03.txt");
        player.onStart();
        player.setMap(*map);

        /*
        auto e = std::make_shared<Enemy>();
        e->transform.setPos(300.f, 400.0f);
        e->setMap(*map);
        e->onStart();
        EnemyManager::getIns()->addActor(e);
        */

        /*
        for(int i = 0; i < 5; ++i) {
            auto e = std::make_shared<Enemy>();
            e->transform.setPos(400.f + 50.f * i, 500.0f);
            e->setMap(*map);
            e->onStart();
            EnemyManager::getIns()->addActor(e);

            auto tem = std::make_shared<Item>();
            tem->transform.setPos(1000.f + 50.0f * i, 500.0f);
            tem->onStart();
            ItemManager::getIns()->addItem(tem);
        }
        */
        
    }

    void Game::onUpdate()
    {
        fps.onUpdate();

        {
            //bg.draw();
            map->drawMap();
            player.onUpdate();

            
            //EnemyManager::getIns()->onUpdateEnemyList();
            //EnemyManager::getIns()->collisionPlayer(player);

            /*
            BulletManager::getIns()->onUpdateBulletList();
            BulletManager::getIns()->collisionMap(*map);
            BulletManager::getIns()->collisionActor(player);

            ItemManager::getIns()->onUpdateItemList();
            ItemManager::getIns()->collisionPlayer(player);
            */

            //fps.drawFps();
        }

        fps.wait();
    }

    void Game::onFinal()
    {

    }
}