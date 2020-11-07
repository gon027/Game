#include "Game.h"

namespace gnGame {

    Game::Game()
        : camera()
        , map(&camera)
        , player(&camera, map)
        , e(&camera, map)
    {
    }

    void Game::onStart()
    {
        camera.onStart();
        map.loadMapFile("MapData/Test_Map.txt");
        player.onStart();
        player.setMap(map);
        e.onStart();
        e.setMap(map);
    }

    void Game::onUpdate()
    {
        map.drawMap();
        player.onUpdate();
        e.onUpdate();

        camera.onUpdate();
    }
}