#pragma once

#include "Game.h"

#include <deque>
#include <set>

class Solver {
public:
    Solver() = default;

    [[nodiscard]] std::vector<Direction> Solve(const Game& root);

private:
    void TryMove(Game current_position, Direction direction);
    void ExploreOne();

    Game root_;
    std::deque<Game> unexplored_;
    std::set<Game> explored_;
};
