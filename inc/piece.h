#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include <SFML/System.hpp>
#include <color.h>
#include <tetromino.h>

namespace tetris {

struct piece {
    auto indices() const;

    tetromino shape{};
    tetris::color color{};
    sf::Vector2i pos{};
    int turns{};
};

inline auto piece::indices() const {
    return tetris::indices(shape)
        | transform::rotate{.turns = turns}
        | transform::move{.offset = pos};
}

}

#endif

