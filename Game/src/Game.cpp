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
        map->loadMapFile("MapData/Test_Map.txt");
        player.onStart();
        player.setMap(*map);
    }

    void Game::onUpdate()
    {
        map->drawMap();
        player.onUpdate();

        //camera.onUpdate();
    }

    void Game::onFinal()
    {
        CameraIns->destroy();
    }
}