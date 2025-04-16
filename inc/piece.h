#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include <SFML/System.hpp>
#include <color.h>
#include <tetromino.h>

namespace tetris {

struct piece {
    tetromino shape{};
    tetris::color color{};
    sf::Vector2i pos{};
    int turns{};
};

}

#endif

