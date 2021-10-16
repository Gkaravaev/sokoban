#include "Point.h"

Point Point::Move(Direction direction, size_t distance) {
    switch (direction) {
        case Direction::DOWN: return {x, y + distance};
        case Direction::UP: return {x, y - distance};
        case Direction::LEFT: return {x - distance, y};
        case Direction::RIGHT: return {x + distance, y};
    }
}