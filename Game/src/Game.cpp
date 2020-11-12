#include "../include/Game.h"

namespace gnGame {

    Game::Game()
        //: camera()
        : map(new Map())
        , player(*map)
    {
    }

    Game::~Game()
    {
        delete map;
    }

    void Game::onStart()
    {
        //camera.onStart();
        map->loadMapFile("Asset/MapData/Test_Map.txt");
        player.onStart();
        player.setMap(*map);
    }

    void Game::onUpdate(float _deltaTime)
    {
        map->drawMap();
        player.onUpdate(_deltaTime);

        //camera.onUpdate();
    }

    void Game::onFinal()
    {
        CameraIns->destroy();
    }
}