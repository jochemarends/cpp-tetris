#ifndef TETRIS_COLOR_H
#define TETRIS_COLOR_H

#include <SFML/Graphics.hpp>

namespace tetris {

enum class color {
    transparent,
    green,
    red,
};

[[nodiscard]] constexpr sf::Color to_rgba(color c) {
    switch (c) {
        case color::transparent:
            return sf::Color::Transparent;
        case color::green:
            return sf::Color::Green;
        case color::red:
            return sf::Color::Red;
        default:
            std::unreachable();
    }
}

}

#endif

