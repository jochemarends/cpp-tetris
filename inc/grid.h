#ifndef SNAKE_GRID_H
#define SNAKE_GRID_H

#include <array>
#include <cstddef>
#include <ranges>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace tetris {

template<std::size_t Rows, std::size_t Columns>
struct grid : sf::Drawable {
    grid(sf::Vector2f top_left, std::size_t tile_size);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
    * Obtain the position of the grid's top left corner.
    */
    [[nodiscard]] sf::Vector2f top_left() const;

    /**
    * Obtain the grid's tile size.
    */
    [[nodiscard]] std::size_t tile_size() const;


    /**
    * Access a grid's tile.
    *
    * @return Reference to color of the tile.
    */
    template<typename Self>
    auto&& operator[](this Self&& self, std::size_t row, std::size_t column);

    /**
    * Obtain the cartesian product of rows and columns.
    */
    [[nodiscard]] auto indices() const;
private:
    std::array<sf::Color, Rows * Columns> tiles_{};
    sf::Vector2f top_left_{};
    std::size_t tile_size_{};
};

template<std::size_t Rows, std::size_t Columns>
grid<Rows, Columns>::grid(sf::Vector2f top_left, std::size_t tile_size) 
    : top_left_{top_left}, tile_size_{tile_size} {}

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape tile{sf::Vector2f{static_cast<float>(tile_size_), static_cast<float>(tile_size_)}};

    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(- (10 / 2.0f));

    for (auto [row, column] : indices()) {
        sf::Vector2f pos{top_left_};

        pos.y += static_cast<float>(row * tile_size_);
        pos.x += static_cast<float>(column * tile_size_);

        sf::Color color{operator[](row, column)};
        tile.setPosition({pos.x, pos.y});
        tile.setFillColor(color);
        target.draw(tile, states);
    }
}

template<std::size_t Rows, std::size_t Columns>
sf::Vector2f grid<Rows, Columns>::top_left() const {
    return top_left_;
}

template<std::size_t Rows, std::size_t Columns>
std::size_t grid<Rows, Columns>::tile_size() const {
    return tile_size_;
}

template<std::size_t Rows, std::size_t Columns>
template<typename Self>
auto&& grid<Rows, Columns>::operator[](this Self&& self, std::size_t row, std::size_t column) {
    if (row >= Rows || column >= Columns) {
        throw std::out_of_range{"attempted to access a tile that is out of range"};
    }
    return self.tiles_[row * Columns + column];
}

template<std::size_t Rows, std::size_t Columns>
auto grid<Rows, Columns>::indices() const {
    auto row_indices = std::views::iota(0uz, Rows);
    auto column_indices = std::views::iota(0uz, Columns);
    return std::views::cartesian_product(row_indices, column_indices);
}

}

#endif

