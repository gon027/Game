#include "../include/Game.h"
#include "../include/WindowInfo.h"
#include "../include/EnemyManager.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"
#include "../include/Item.h"
#include "../include/ItemManager.h"
#include "../include/ShotEnemy.h"
#include "../include/BigEnemy.h"
#include "../include/WalkEnemy.h"
#include <memory>

namespace gnGame {

    static std::string MapFile = "Asset/MapData/";

    Game::Game()
        : map(new Map())
        , player()
        , fps()
        , bg(Vector2{WindowInfo::WindowWidth / 2.0f, WindowInfo::WindowHeight / 2.0f})
        , te({100, 900})
        , mapList(4)
    {
        mapList[0] = "TestMap_01.txt";
        mapList[1] = "TestMap_02.txt";
        mapList[2] = "TestMap_03.txt";
        mapList[3] = "TestMap_04.txt";
    }

    Game::~Game()
    {
        delete map;
    }

    void Game::onStart()
    {
        bg.setTexture();
        map->loadMapFile(MapFile + mapList[currentMap]);
        Camera::setMapInfo(map->getMapSize());

        player.onStart();
        player.setMap(map);
        player.transform.setPos(100, 300);

        te.onStart();

        /*
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

        auto bb = std::shared_ptr<Enemy>(new BigEnemy{});
        bb->transform.setPos(500.f, 750.0f);
        bb->setMap(map);
        bb->onStart();
        EnemyManager::getIns()->addActor(bb);

        auto t = std::shared_ptr<Enemy>(new WalkEnemy{});
        t->transform.setPos(300.f, 750.0f);
        t->setMap(map);
        t->onStart();
        EnemyManager::getIns()->addActor(t);
        
        for(int i = 0; i < 5; ++i) {
            auto tem = std::shared_ptr<Item>(new Item{});
            tem->transform.setPos(300.f + 50.0f * i, 790.0f);
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

            te.onUpdate();

            if (te.getCollider().isHitTest(player.getCollider())) {
                te.onEvent();
            }

            
            if (Input::getKeyDown(Key::C)) {
                currentMap = (currentMap + 1) % 4;
                map->claerMap();
                map->loadMapFile(MapFile + mapList[currentMap]);
                Camera::setMapInfo(map->getMapSize());
                player.transform.setPos(100, 50);
            }
            
            /*
            EnemyManager::getIns()->onUpdateEnemyList();
            EnemyManager::getIns()->collisionPlayer(player);
            
            BulletManager::getIns()->onUpdateBulletList();
            BulletManager::getIns()->collisionMap(*map);
            BulletManager::getIns()->collisionActor(player);

            ItemManager::getIns()->onUpdateItemList();
            ItemManager::getIns()->collisionPlayer(player);
            */
        }

        fps.wait();
    }

    void Game::onFinal()
    {

    }
}