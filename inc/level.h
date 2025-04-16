#ifndef TETRIS_LEVEL_H
#define TETRIS_LEVEL_H

#include "grid.h"
#include "piece.h"
#include "tetromino.h"

namespace tetris {

enum class action {
    move_left,
    move_right,
    move_down,
    rotate_left,
    rotate_right,
};

struct level : sf::Drawable {
    level(sf::Vector2f top_left, std::size_t tile_size);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void tick();

    void spawn(tetromino t, color c);

    bool move_left();
    bool move_right();
    bool move_down();

    bool turn_cw();
    bool turn_ccw();

    static constexpr std::size_t rows{20uz};
    static constexpr std::size_t columns{10uz};
private:
    static constexpr sf::Vector2i spawn_pos_{3, 3};
    piece active_piece_{ .pos = spawn_pos_ };
    grid<rows, columns> grid_;
};

}

#endif

