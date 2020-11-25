#include "../include/Grid.h"

namespace gnGame {

    Grid::Grid() 
        : ptr(nullptr)
        , width(0)
        , height(0)
        , length(width* height)
    {

    }

    Grid::Grid(int _width, int _height, int _value)
        : ptr(new int[_width * _height])
        , width(_width)
        , height(_height)
        , length(width* height)
    {
        fill(_value);
    }

    Grid::~Grid()
    {
        if (ptr) {
            delete[] ptr;
            ptr = nullptr;
        }
    }

    void Grid::create(int _width, int _height, int _value)
    {
        width = _width;
        height = _height;
        length = width * height;
        ptr = new int[length];
        fill(_value);
    }

    void Grid::fill(int _value) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                ptr[toIndex(j, i)] = _value;
            }
        }
    }

    void Grid::setValue(int _x, int _y, int _value) {
        if (checkIndex(_x, _y)) {
            return;
        }
        ptr[toIndex(_x, _y)] = _value;
    }

    int Grid::getValue(int _x, int _y) {
        if (checkIndex(_x, _y)) {
            return -1;
        }
        return ptr[toIndex(_x, _y)];
    }

    int Grid::getWidth() {
        return width;
    }

    int Grid::getHeight() {
        return height;
    }

    int Grid::getLength() {
        return length;
    }

    int Grid::toIndexX(int _x) {
        return _x % width;
    }

    int Grid::toIndexY(int _y) {
        return _y / width;
    }

    int Grid::toIndex(int _x, int _y) {
        return _y * width + _x;
    }

    bool Grid::checkIndex(int _x, int _y) {
        if (_x < 0 || _x >= width || _y < 0 || _y >= height) {
            return true;
        }
        return false;
    }

}