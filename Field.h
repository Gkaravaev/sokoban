#pragma once

#include "Point.h"
#include "Cell.h"
#include <vector>

class Field {
public:
    Field() = default;
    explicit Field(std::vector<std::vector<Cell>> field);

    [[nodiscard]] Cell Get(Point point) const;
    void Set(Point point, Cell state);
    Point GetSize();

    [[nodiscard]] std::vector<std::vector<Cell>> GetData() const;

private:
    std::vector<std::vector<Cell>> field_;
};
