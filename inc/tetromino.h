#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <array>
#include <span>
#include <utility>
#include <SFML/System/Vector2.hpp>

namespace tetris {

enum class tetromino {
    i,
};

constexpr std::span<const sf::Vector2i> shape(tetromino t) {
    switch (t) {
        case tetromino::i: {
            static constexpr std::array offsets{
                sf::Vector2i{0, -1},
                sf::Vector2i{0, 0},
                sf::Vector2i{0, 1},
                sf::Vector2i{0, 2},
            };
            return std::span{offsets};
        }
        default:
            std::unreachable();
    }
}
    
};

#endif

