#include "Game.h"

namespace gnGame {

    Game::Game()
        : camera()
        , map(new Map(&camera))
        , player(&camera, *map)
    {
    }

    Game::~Game()
    {
        delete map;
    }

    void Game::onStart()
    {
        camera.onStart();
        map->loadMapFile("MapData/Test_Map.txt");
        player.onStart();
        player.setMap(*map);
    }

    void Game::onUpdate()
    {
        map->drawMap();
        player.onUpdate();

        camera.onUpdate();
    }
}