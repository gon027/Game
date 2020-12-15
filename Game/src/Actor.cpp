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
        // MN: 64.0f : ��ʂ̃I�t�Z�b�g
        auto deathBorder = _fallBorder + 64.0f;

        // ����̃{�[�_�[�����W���傫���Ȃ�Ǝ��S����
        return this->transform.pos.y >= deathBorder;
    }
}
