#include "../include/Game.h"
#include "../include/Global.h"
#include "../include/WindowInfo.h"
#include "../include/TextureManager.h"
#include "../include/EnemyManager.h"
#include "../include/BulletManager.h"
#include "../include/ItemManager.h"
#include "../include/EventManager.h"

namespace gnGame {

    Game::Game()
        : map(new Map{ nullptr })
        , player()
        , fps()
        , bg()
        , mapList(4)
    {
        mapList[0] = "TestMap_1";
        mapList[1] = "TestMap_2";
        mapList[2] = "TestMap_3";
        mapList[3] = "TestMap_4";
    }

    Game::~Game()
    {
        delete map;
    }

    void Game::onStart()
    {
        map->loadMapFile(global::MapAsset(mapList[currentMap]));
        Camera::setMapInfo(map->getMapSize());

        player.onStart();
        player.setMap(map);
        player.initPosition({ 100, 300 });
    }

    void Game::onUpdate()
    {
        fps.onUpdate();

        {
            //bg.draw();
            map->drawMap();
            player.onUpdate();

            //if (Input::getKeyDown(Key::C)) {
            //    nextStage();
            //}
            
            EnemyManager::getIns()->onUpdateEnemyList();
            EnemyManager::getIns()->collisionPlayer(player);
            
            BulletManager::getIns()->onUpdateBulletList();
            BulletManager::getIns()->collisionMap(*map);
            BulletManager::getIns()->collisionActor(player, nullptr);

            ItemManager::getIns()->onUpdateItemList();
            ItemManager::getIns()->collisionPlayer(player);

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
        // Managerのリストをすべて消去
        resetMap();

        // マップの数を1つ進める
        currentMap = (currentMap + 1) % 4;

        // マップをクリアする
        map->claerMap();

        // マップを読み込む
        map->loadMapFile(global::MapAsset(mapList[currentMap]));

        // カメラをマップに収める
        Camera::setMapInfo(map->getMapSize());

        player.transform.setPos(100, 50);
    }
}