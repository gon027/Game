#include "../include/Game.h"
#include "../include/WindowInfo.h"
#include "../include/EnemyManager.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"
#include "../ItemManager.h"
#include "../include/ShotEnemy.h"
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
        map->loadMapFile("Asset/MapData/TestMap_01.txt");
        Camera::setMapInfo(map->getMapSize());

        player.onStart();
        player.setMap(map);

        
        auto e = std::shared_ptr<Enemy>(new Enemy{});
        e->transform.setPos(500.f, 700.0f);
        e->setMap(map);
        e->onStart();
        EnemyManager::getIns()->addActor(e);

        auto ee = std::shared_ptr<Enemy>(new ShotEnemy{});
        ee->transform.setPos(500.f, 200.0f);
        ee->setMap(map);
        ee->onStart();
        EnemyManager::getIns()->addActor(ee);
        

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
            player.onUpdate();
            map->drawMap();
            
           

            
            EnemyManager::getIns()->onUpdateEnemyList();
            EnemyManager::getIns()->collisionPlayer(player);

            
            BulletManager::getIns()->onUpdateBulletList();
            BulletManager::getIns()->collisionMap(*map);
            BulletManager::getIns()->collisionActor(player);

            /*
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