#include "Field.h"

Field::Field(std::vector<std::vector<Cell>> field) : field_(std::move(field)) {};

Cell Field::Get(Point point) const {
    if (field_.size() <= point.y || field_.at(0).size() <= point.x) {
        return Cell::INVALID;
    }
    return field_.at(point.y).at(point.x);
}

void Field::Set(Point point, Cell state) {
    field_.at(point.y).at(point.x) = state;
}

Point Field::GetSize() {
    return {field_.at(0).size(), field_.size()};
}

std::vector <std::vector<Cell>> Field::GetData() const {
    return field_;
}
