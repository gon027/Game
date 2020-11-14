#include "../include/Game.h"
#include "../include/EnemyManager.h"
#include <memory>

namespace gnGame {

    Game::Game()
        : map(new Map())
        , player()
        //, enemy()
        , fps()
    {
    }

    Game::~Game()
    {
        delete map;
    }

    void Game::onStart()
    {
        map->loadMapFile("Asset/MapData/MapTest03.txt");
        player.onStart();
        player.setMap(*map);

        //enemy.onStart();
        //enemy.setMap(*map);
    }

    void Game::onUpdate(float _deltaTime)
    {
        fps.onUpdate();

        {
            map->drawMap();
            player.onUpdate(_deltaTime);
            //enemy.onUpdate(_deltaTime);
            fps.draw();
        }

        fps.wait();
    }

    void Game::onFinal()
    {
        CameraIns->destroy();
    }
}