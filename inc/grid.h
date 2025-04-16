#ifndef TETRIS_GRID_H
#define TETRIS_GRID_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <color.h>
#include <piece.h>

namespace tetris {

template<std::size_t Rows, std::size_t Columns>
struct grid : sf::Drawable {
    grid(sf::Vector2f top_left, std::size_t tile_size);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
    * Obtain the position of the grid's top left corner.
    */
    [[nodiscard]] sf::Vector2f top_left() const;

    /**
    * Obtain the grid's tile size in pixels.
    */
    [[nodiscard]] std::size_t tile_size() const;

    /**
     * Obtain grid's size in pixels.
     */
    [[nodiscard]] sf::Vector2<std::size_t> size() const;

    /**
     * Clear the grid.
     */
    void clear();

    /**
     * Set all tiles to one color.
     */
    void fill(color c);

    /**
     * Write a tetromino piece to the grid.
     *
     * @return Number of tiles that were written to.
     */
    int write(const piece& p);

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
    std::array<color, Rows * Columns> tiles_{};
    sf::Vector2f top_left_{};
    std::size_t tile_size_{};
};

template<std::size_t Rows, std::size_t Columns>
grid<Rows, Columns>::grid(sf::Vector2f top_left, std::size_t tile_size) 
    :top_left_{top_left}, tile_size_{tile_size} {}

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape tile{sf::Vector2f{static_cast<float>(tile_size_), static_cast<float>(tile_size_)}};

    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(- (10 / 2.0f));

    for (auto [row, column] : indices()) {
        sf::Vector2f pos{top_left_};

        pos.y += static_cast<float>(row * tile_size_);
        pos.x += static_cast<float>(column * tile_size_);

        sf::Color color{to_rgba(operator[](row, column))};
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
sf::Vector2<std::size_t> grid<Rows, Columns>::size() const {
    return sf::Vector2<std::size_t>{tile_size_ * Rows, tile_size_ * Columns};
}

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::clear() {
    fill(color::transparent);
}

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::fill(color c) {
    std::ranges::fill(tiles_, c);
}

template<std::size_t Rows, std::size_t Columns>
int grid<Rows, Columns>::write(const piece& p) {
    auto indices = tetris::indices(p.shape)
        | transform::rotate{.turns = p.turns}
        | transform::move{.offset = p.pos};

    for (auto [row, column] : indices) {
        operator[](row, column) = p.color;
    }

    return 1;
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

