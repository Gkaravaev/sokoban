#include "Game.h"
#include "Solver.h"

#include <iostream>

namespace {

    std::vector<std::string> Read() {
        std::vector<std::string> answer;
        std::string input;
        std::cin >> input;
        while (input != "END") {
            answer.push_back(input);
            std::cin >> input;
        }
        return answer;
    }

    Cell ParseSymbol(char ch) {
        switch (ch) {
            case '#': return Cell::WALL;
            case '.': return Cell::EMPTY;
            case '*': return Cell::PLAYER;
            case 'o': return Cell::CRATE;
            case 'x': return Cell::TARGET;
            case '!': return Cell::CRATE_ON_TARGET;
            case '@': return Cell::PLAYER_ON_TARGET;
            default: return Cell::INVALID;
        }
    }

    std::string PrintCell(Cell cell) {
        switch (cell) {
            case Cell::EMPTY: return ".";
            case Cell::WALL: return "#";
            case Cell::PLAYER: return "*";
            case Cell::CRATE: return "o";
            case Cell::TARGET: return "x";
            case Cell::CRATE_ON_TARGET: return "!";
            case Cell::PLAYER_ON_TARGET: return "@";
            case Cell::INVALID: return "~";
        }
    }

    std::string PrintDirection(Direction direction) {
        switch (direction) {
            case Direction::LEFT: return "←";
            case Direction::RIGHT: return "→";
            case Direction::DOWN: return "↓";
            case Direction::UP: return "↑";
        }
    }

    std::vector<std::vector<Cell>> ParseMap(const std::vector<std::string>& text_map) {
        std::vector<std::vector<Cell>> cell_map;
        for (const auto& line : text_map) {
            cell_map.emplace_back();
            std::transform(line.begin(), line.end(), std::back_inserter(cell_map.back()), ParseSymbol);
        }
        return cell_map;
    }

    void PrintMap(const std::vector<std::vector<Cell>>& map) {
        for (const auto& row : map) {
            for (const auto cell : row) {
                std::cout << PrintCell(cell);
            }
            std::cout << std::endl;
        }
    }

    void PrintSequence(const std::vector<Direction>& sequence) {
        for (const auto& move : sequence) {
            std::cout << PrintDirection(move);
        }
        std::cout << std::endl;
    }
}


int main() {
    std::cout << "Welcome to the Sokoban solver!" << std::endl
            << "Enter your puzzle below using these symbols:" << std::endl << "\".\" for an empty space" << std::endl
            << "\"#\" for a wall" << std::endl << "\"*\" for the player" << std::endl << "\"o\" for a crate"
            << std::endl << "\"x\" for a target" << std::endl << "\"!\" for a crate on a target" << std::endl
            << "\"@\" for the player on a target" << std::endl << "Enter \"END\" to finish!" << std::endl;
    Solver solver;
    try {
        auto game = Game(ParseMap(std::move(Read())));
        auto seq = solver.Solve(game);
        if (seq.empty()) {
            if (game.CheckWin()) {
                std::cout << "Already solved!" << std::endl;
            } else {
                std::cout << "Impossible!" << std::endl;
            }
        } else {
            std::cout << "Can be solved in " << seq.size() << " moves!" << std::endl;
            PrintSequence(seq);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}