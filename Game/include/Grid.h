#ifndef GRID_H
#define GRID_H

#include <memory>

namespace gnGame {
    class Grid {
    public:
        Grid();
        Grid(int _width, int _height, int _value = 0);
        ~Grid();

        // �z����쐬����
        void create(int _width, int _height, int _value = 0);

        // �z���_value�œh��Ԃ�
        void fill(int _value = 0);

        // �z��̒l���擾
        int getValue(int _x, int _y);

        // �z��ɒl��ݒ肷��
        void setValue(int _x, int _y, int _value);

        // �z����N���A����
        void claer();

        int getWidth();     // Width���擾
        int getHeight();    // Height���擾
        int getLength();    // �z��̒������擾

        int toIndexX(int _x);  // �l��X���W�ɕϊ�
        int toIndexY(int _y);  // �l��Y���W�ɕϊ�

    private:
        // �z���Index�֕ϊ�
        int toIndex(int _x, int _y);

        // (x, y)���z������m�F����
        bool checkIndex(int _x, int _y);

    private:
        int* ptr;
        int width;
        int height;
        int length;
    };
}

#endif // !GRID_H