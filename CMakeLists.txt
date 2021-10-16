project(sokoban)

set(CMAKE_CXX_STANDARD 20)

add_executable(sokoban main.cpp Point.h Field.cpp Field.h Point.cpp Direction.h Game.cpp Game.h Cell.h Solver.cpp Solver.h)