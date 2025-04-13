#ifndef TETRIS_LEVEL_H
#define TETRIS_LEVEL_H

#include "grid.h"

namespace tetris {

struct level {
    level(sf::Vector2f top_left, std::size_t tile_size);

    static constexpr std::size_t rows{20uz};
    static constexpr std::size_t columns{10uz};
private:
    grid<rows, columns> grid_;
};

}

#endif

