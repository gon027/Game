#include "../include/Actor.h"
#include "../include/WindowInfo.h"
#include "../include/Camera.h"

namespace gnGame {

    IActor::IActor()
        : velocity()
        , bounds()
        , intersectPoint()
    {}

    bool IActor::isOnScreen()
    {
        auto minScrenn = Camera::minScreenPos();
        auto maxScreen = Camera::maxScreenPos();

        return transform.pos.x >= minScrenn.x && transform.pos.x <= maxScreen.x
            && transform.pos.y >= minScrenn.y && transform.pos.y <= maxScreen.y;
    }
}
