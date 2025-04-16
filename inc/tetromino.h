#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <cmath>
#include <numbers>
#include <ranges>
#include <span>
#include <utility>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace tetris {

enum class tetromino {
    i,
};

constexpr std::span<const sf::Vector2i> indices(tetromino t) {
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

namespace transform {

struct move : std::ranges::range_adaptor_closure<move> {
    constexpr auto operator()(std::ranges::input_range auto&& indices) const {
        return indices | std::views::transform([this](sf::Vector2i index) {
            return index + offset;
        }) | std::ranges::to<std::vector>();
    }
    sf::Vector2i offset{};
};

struct rotate : std::ranges::range_adaptor_closure<rotate> {
    constexpr auto operator()(std::ranges::input_range auto&& indices) const {
        double radians = turns * (std::numbers::pi / 2.0);

        return indices | std::views::transform([radians](sf::Vector2i index) {
            const int row = std::lround(index.y * std::sin(radians) + index.x * std::cos(radians));
            const int column = std::lround(index.y * std::cos(radians) - index.x * std::sin(radians));
            return sf::Vector2i{row, column};
        }) | std::ranges::to<std::vector>();
    }
    int turns{};
};

}
    
};

#endif

