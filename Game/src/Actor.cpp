#include "../include/Actor.h"
#include "../include/WindowInfo.h"
#include "../include/Camera.h"

namespace gnGame {

    IActor::IActor()
        : velocity()
        , bounds()
        , intersectPoint()
    {}

    bool IActor::onScreen()
    {
        return transform.pos.x >= 0 && transform.pos.x <= WindowInfo::WindowWidth
            && transform.pos.y >= 0 && transform.pos.y <= WindowInfo::WindowHeight;
    }
}
