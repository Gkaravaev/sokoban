#include "Solver.h"

void Solver::TryMove(Game current_position, Direction direction) {
    current_position.Move(direction);
    if (!explored_.contains(current_position)) {
        explored_.insert(current_position);
        unexplored_.push_back(current_position);
    }
}

void Solver::ExploreOne() {
    TryMove(unexplored_.front(), Direction::LEFT);
    TryMove(unexplored_.front(), Direction::RIGHT);
    TryMove(unexplored_.front(), Direction::UP);
    TryMove(unexplored_.front(), Direction::DOWN);
    unexplored_.pop_front();
}

std::vector<Direction> Solver::Solve(const Game& root) {
    root_ = root;
    explored_.clear();
    unexplored_.clear();
    unexplored_.push_back(root);
    while (!unexplored_.empty()) {
        if (unexplored_.front().CheckWin()) {
            Game win = unexplored_.front();
            unexplored_.clear();
            explored_.clear();
            return win.GetMoveSequence();
        }
        ExploreOne();
    }
    unexplored_.clear();
    explored_.clear();
    return {};
}