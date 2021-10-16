#pragma once

#include "Field.h"

class Game {
public:
    Game() = default;
    explicit Game(const std::vector<std::vector<Cell>>& field);

    void Move(Direction direction);
    bool CheckWin();
    [[nodiscard]] std::vector<std::vector<Cell>> GetData() const;
    [[nodiscard]] std::vector<Direction> GetMoveSequence() const;

    bool operator<(const Game& other) const;

private:
    Field field_;
    Point player_position_{};
    std::vector<Direction> sequence_;
};
