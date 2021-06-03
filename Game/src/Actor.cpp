#include "../include/Actor.h"
#include "../include/WindowInfo.h"
#include "../include/Camera.h"
#include "../include/ObjectManager.h"

namespace gnGame {

    Actor::Actor()
        : velocity()
        , bounds()
        , intersectPoint()
    {
        ObjectManager::getIns()->addObject(this);
    }

    bool Actor::fallScreen(float _fallBorder)
    {
        auto deathBorder = _fallBorder + 64.0f;

        // ����̃{�[�_�[�����W���傫���Ȃ�Ǝ��S����
        return this->transform.pos.y >= deathBorder;
    }
}
