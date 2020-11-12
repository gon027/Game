#include "../include/Game.h"

namespace gnGame {

    Game::Game()
        //: camera()
        : map(new Map())
        , player(*map)
        , fps()
    {
    }

    Game::~Game()
    {
        delete map;
    }

    void Game::onStart()
    {
        //camera.onStart();
        map->loadMapFile("Asset/MapData/MapTest03.txt");
        player.onStart();
        player.setMap(*map);
    }

    void Game::onUpdate(float _deltaTime)
    {
        fps.onUpdate();

        {
            map->drawMap();
            player.onUpdate(_deltaTime);

            //camera.onUpdate();
            fps.draw();
        }

        fps.wait();
    }

    void Game::onFinal()
    {
        CameraIns->destroy();
    }
}