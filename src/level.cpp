#include "level.h"

namespace tetris {

level::level(sf::Vector2f top_left, std::size_t tile_size)
    :grid_{top_left, tile_size} {}

void level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(grid_, states);
}

void level::tick() {
    grid_.clear();

    // for (auto offset : tetris::indices(active_piece_.shape)) {
    //     auto [column, row] = active_piece_.pos + offset;
    //     grid_[column, row] = color::red;
    // }

    active_piece_.color = color::red;
    grid_.write(active_piece_);
    // ++active_piece_.pos.x;
    turn_cw();
}

void level::spawn(tetromino t, color c) {
    return;
    for (auto offset : tetris::indices(t)) {
        auto [column, row] = spawn_pos_ + offset;
        grid_[column, row] = c;
    }
}

bool level::turn_cw() {
    ++active_piece_.turns;
    return false;
}

}

