#ifndef GRID_H
#define GRID_H

#include <memory>

namespace gnGame {
    class Grid {
    public:
        Grid();
        Grid(int _width, int _height, int _value = 0);
        ~Grid();

        // 配列を作成する
        void create(int _width, int _height, int _value = 0);

        // 配列を_valueで塗りつぶす
        void fill(int _value = 0);

        // 配列の値を取得
        int getValue(int _x, int _y);

        // 配列に値を設定する
        void setValue(int _x, int _y, int _value);

        // 配列をクリアする
        void claer();

        int getWidth();     // Widthを取得
        int getHeight();    // Heightを取得
        int getLength();    // 配列の長さを取得

        int toIndexX(int _x);  // 値をX座標に変換
        int toIndexY(int _y);  // 値をY座標に変換

    private:
        // 配列のIndexへ変換
        int toIndex(int _x, int _y);

        // (x, y)が配列内か確認する
        bool checkIndex(int _x, int _y);

    private:
        int* ptr;
        int width;
        int height;
        int length;
    };
}

#endif // !GRID_H