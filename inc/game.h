#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <cstddef>

namespace tetris {

struct game {
    void tick();

    static constexpr std::size_t width{400uz};
    static constexpr std::size_t height{800uz};
};

}

#endif

