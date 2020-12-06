#include "../include/Game.h"
#include "../include/Global.h"
#include "../include/WindowInfo.h"
#include "../include/TextureManager.h"
#include "../include/EnemyManager.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"
#include "../include/ItemManager.h"
#include "../include/Item.h"
#include "../include/ShotEnemy.h"
#include "../include/BigEnemy.h"
#include "../include/WalkEnemy.h"
#include "../include/EventObject.h"
#include "../include/StageEvent.h"
#include "../EventManager.h"
#include <memory>

namespace gnGame {

    Game::Game()
        : map(new Map())
        , player()
        , fps()
        , bg(Vector2{WindowInfo::WindowWidth / 2.0f, WindowInfo::WindowHeight / 2.0f})
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
        map->loadMapFile(global::MapAsset(mapList[currentMap]));
        Camera::setMapInfo(map->getMapSize());

        player.onStart();
        player.setMap(map);
        player.initPosition({ 100, 300 });

        auto e1 = EventPtr(new StageEvent({ 1264, 112 }, this));
        e1->onStart();
        EventManager::getIns()->addEvent(e1);

        auto e2 = EventPtr(new StageEvent({ 1264, 144 }, this));
        e2->onStart();
        EventManager::getIns()->addEvent(e2);

        auto e3 = EventPtr(new StageEvent({ 1264, 176 }, this));
        e3->onStart();
        EventManager::getIns()->addEvent(e3);

        auto e4 = EventPtr(new StageEvent({ 1264, 208 }, this));
        e4->onStart();
        EventManager::getIns()->addEvent(e4);
    }

    void Game::onUpdate()
    {
        fps.onUpdate();

        {
            //bg.draw();
            map->drawMap();
            player.onUpdate();

            if (Input::getKeyDown(Key::C)) {
                nextStage();
            }
            
            /*
            EnemyManager::getIns()->onUpdateEnemyList();
            EnemyManager::getIns()->collisionPlayer(player);
            */

            BulletManager::getIns()->onUpdateBulletList();
            BulletManager::getIns()->collisionMap(*map);
            BulletManager::getIns()->collisionActor(player);
            /*
            ItemManager::getIns()->onUpdateItemList();
            ItemManager::getIns()->collisionPlayer(player);
            */

            EventManager::getIns()->collisionPlayer(player);
            EventManager::getIns()->onUpdateEventList();

        }

        fps.wait();
    }

    void Game::onFinal()
    {

    }

    Player* Game::getPlayer()
    {
        return &player;
    }

    Map* Game::getMap()
    {
        return map;
    }

    void Game::resetMap()
    {
        EnemyManager::getIns()->claerList();

        BulletManager::getIns()->claerList();
        
        ItemManager::getIns()->claerList();
    }

    void Game::nextStage()
    {
        currentMap = (currentMap + 1) % 4;
        map->claerMap();
        map->loadMapFile(global::MapAsset(mapList[currentMap]));
        Camera::setMapInfo(map->getMapSize());
        player.transform.setPos(100, 50);
    }
}