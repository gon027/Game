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
        , fps()
        , bg(Vector2{WindowInfo::WindowWidth / 2.0f, WindowInfo::WindowHeight / 2.0f})
        , item()
    {
    }

    Game::~Game()
    {
        delete map;
    }

    void Game::onStart()
    {
        bg.setTexture();
        map->loadMapFile("Asset/MapData/Test_Map.txt");
        player.onStart();
        player.setMap(*map);
        item.onStart();

        for(int i = 0; i < 5; ++i) {
            auto e = std::make_shared<Enemy>();
            e->transform.setPos(400.f + 20.f * i, 500.0f);
            e->setMap(*map);
            e->onStart();
            EnemyManager::getIns()->addActor(e);
        }
        
    }

    void Game::onUpdate()
    {
        fps.onUpdate();

        {
            bg.draw();
            map->drawMap();
            player.onUpdate();
            item.onUpdate();

            if (item.getCollider().isHitTest(player.getCollider())) {
                item.setActive(false);
            }

            EnemyManager::getIns()->onUpdateEnemyList();
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