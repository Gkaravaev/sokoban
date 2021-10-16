#pragma once

#include "Direction.h"

struct Point {
    Point Move(Direction direction, size_t distance = 1);

    size_t x;
    size_t y;
};

