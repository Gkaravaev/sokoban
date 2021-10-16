#pragma once

enum class Cell {
    EMPTY,
    WALL,
    CRATE,
    TARGET,
    CRATE_ON_TARGET,
    PLAYER,
    PLAYER_ON_TARGET,
    INVALID,
};