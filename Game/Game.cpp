#include "Game.h"

namespace gnGame {

    Game::Game()
        : camera()
        , map(&camera)
        , player(&camera, map)
    {
    }

    void Game::onStart()
    {
        camera.onStart();
        map.loadMapFile("Map/Test_Map.txt");
        player.setMap(map);
        player.onStart();
    }

    void Game::onUpdate()
    {
        map.drawMap();
        player.onUpdate();
        camera.onUpdate();
    }
}