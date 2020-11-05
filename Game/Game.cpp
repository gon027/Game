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
        player.onStart();
        player.setMap(map);
    }

    void Game::onUpdate()
    {
        map.drawMap();
        player.onUpdate();
        camera.onUpdate();
    }
}