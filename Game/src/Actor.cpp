#include "../include/Actor.h"
#include "../include/WindowInfo.h"
#include "../include/Camera.h"

namespace gnGame {

    IActor::IActor()
        : velocity()
        , bounds()
        , intersectPoint()
    {}

    bool IActor::fallScreen(float _fallBorder)
    {
        // MN: 64.0f : 画面のオフセット
        auto deathBorder = _fallBorder + 64.0f;

        // 既定のボーダーより座標が大きくなると死亡する
        return this->transform.pos.y >= deathBorder;
    }
}
