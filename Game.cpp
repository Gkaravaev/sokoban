#include "Game.h"

#include <stdexcept>

Game::Game(const std::vector<std::vector<Cell>>& field) : field_(field) {
    if (field.empty()) {
        throw std::runtime_error("Empty field!");
    }
    for (size_t i = 1; i < field.size(); ++i) {
        if (field.at(i).size() != field.at(i - 1).size()) {
            throw std::runtime_error("Unequal row lengths!");
        }
    }
    bool player_present = false;
    size_t balance = 0;
    for (size_t x = 0; x < field_.GetSize().x; ++x) {
        for (size_t y = 0; y < field_.GetSize().y; ++y) {
            if (field_.Get({x, y}) == Cell::PLAYER) {
                if (player_present) {
                    throw std::runtime_error("More than one player!");
                }
                player_position_ = {x, y};
                player_present = true;
            } else if (field_.Get({x, y}) == Cell::TARGET || field_.Get({x, y}) == Cell::PLAYER_ON_TARGET) {
                --balance;
            } else if (field_.Get({x, y}) == Cell::CRATE) {
                ++balance;
            } else if (field_.Get({x, y}) == Cell::INVALID) {
                throw std::runtime_error("Invalid cell!");
            }
        }
    }
    if (!player_present) {
        throw std::runtime_error("No player!");
    }
    if (balance != 0) {
        throw std::runtime_error("Unequal amounts of crates and targets!");
    }
}

void Game::Move(Direction direction) {
    if (field_.Get(player_position_.Move(direction)) == Cell::EMPTY) {
        if (field_.Get(player_position_) == Cell::PLAYER_ON_TARGET) {
            field_.Set(player_position_, Cell::TARGET);
        } else {
            field_.Set(player_position_, Cell::EMPTY);
        }
        field_.Set(player_position_.Move(direction), Cell::PLAYER);
        player_position_ = player_position_.Move(direction);
        sequence_.push_back(direction);
    } else if (field_.Get(player_position_.Move(direction)) == Cell::TARGET) {
        if (field_.Get(player_position_) == Cell::PLAYER_ON_TARGET) {
            field_.Set(player_position_, Cell::TARGET);
        } else {
            field_.Set(player_position_, Cell::EMPTY);
        }
        field_.Set(player_position_.Move(direction), Cell::PLAYER_ON_TARGET);
        player_position_ = player_position_.Move(direction);
        sequence_.push_back(direction);
    } else if (field_.Get(player_position_.Move(direction)) == Cell::CRATE &&
               field_.Get(player_position_.Move(direction, 2)) == Cell::EMPTY) {
        if (field_.Get(player_position_) == Cell::PLAYER_ON_TARGET) {
            field_.Set(player_position_, Cell::TARGET);
        } else {
            field_.Set(player_position_, Cell::EMPTY);
        }
        field_.Set(player_position_.Move(direction), Cell::PLAYER);
        field_.Set(player_position_.Move(direction, 2), Cell::CRATE);
        player_position_ = player_position_.Move(direction);
        sequence_.push_back(direction);
    } else if (field_.Get(player_position_.Move(direction)) == Cell::CRATE &&
               field_.Get(player_position_.Move(direction, 2)) == Cell::TARGET) {
        if (field_.Get(player_position_) == Cell::PLAYER_ON_TARGET) {
            field_.Set(player_position_, Cell::TARGET);
        } else {
            field_.Set(player_position_, Cell::EMPTY);
        }
        field_.Set(player_position_.Move(direction), Cell::PLAYER);
        field_.Set(player_position_.Move(direction, 2), Cell::CRATE_ON_TARGET);
        player_position_ = player_position_.Move(direction);
        sequence_.push_back(direction);
    } else if (field_.Get(player_position_.Move(direction)) == Cell::CRATE_ON_TARGET &&
               field_.Get(player_position_.Move(direction, 2)) == Cell::EMPTY) {
        if (field_.Get(player_position_) == Cell::PLAYER_ON_TARGET) {
            field_.Set(player_position_, Cell::TARGET);
        } else {
            field_.Set(player_position_, Cell::EMPTY);
        }
        field_.Set(player_position_.Move(direction), Cell::PLAYER_ON_TARGET);
        field_.Set(player_position_.Move(direction, 2), Cell::CRATE);
        player_position_ = player_position_.Move(direction);
        sequence_.push_back(direction);
    } else if (field_.Get(player_position_.Move(direction)) == Cell::CRATE_ON_TARGET &&
               field_.Get(player_position_.Move(direction, 2)) == Cell::TARGET) {
        if (field_.Get(player_position_) == Cell::PLAYER_ON_TARGET) {
            field_.Set(player_position_, Cell::TARGET);
        } else {
            field_.Set(player_position_, Cell::EMPTY);
        }
        field_.Set(player_position_.Move(direction), Cell::PLAYER_ON_TARGET);
        field_.Set(player_position_.Move(direction, 2), Cell::CRATE_ON_TARGET);
        player_position_ = player_position_.Move(direction);
        sequence_.push_back(direction);
    }
}

bool Game::CheckWin() {
    for (size_t x = 0; x < field_.GetSize().x; ++x) {
        for (size_t y = 0; y < field_.GetSize().y; ++y) {
            if (field_.Get({x, y}) == Cell::CRATE) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::vector<Cell>> Game::GetData() const {
    return field_.GetData();
}

std::vector<Direction> Game::GetMoveSequence() const {
    return sequence_;
}

bool Game::operator<(const Game& other) const {
    return field_.GetData() <=> other.GetData() == std::strong_ordering::less;
}
