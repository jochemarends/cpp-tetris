#include "level.h"
#include <functional>

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
    // turn_cw();
    move_down();
}

void level::spawn(tetromino t, color c) {
    return;
    for (auto offset : tetris::indices(t)) {
        auto [column, row] = spawn_pos_ + offset;
        grid_[column, row] = c;
    }
}

bool level::move_left() {
    --active_piece_.pos.y;

    auto fn = std::bind_front(&decltype(grid_)::contains, grid_);
    auto ok = std::ranges::all_of(active_piece_.indices(), fn);

    if (!ok) {
        ++active_piece_.pos.y;
    }

    return ok;
}

bool level::move_right() {
    ++active_piece_.pos.y;

    auto fn = std::bind_front(&decltype(grid_)::contains, grid_);
    auto ok = std::ranges::all_of(active_piece_.indices(), fn);

    if (!ok) {
        --active_piece_.pos.y;
    }

    return ok;
}

bool level::move_down() {
    ++active_piece_.pos.x;

    auto fn = std::bind_front(&decltype(grid_)::contains, grid_);
    auto ok = std::ranges::all_of(active_piece_.indices(), fn);

    if (!ok) {
        --active_piece_.pos.x;
    }

    return ok;
}

bool level::turn_cw() {
    ++active_piece_.turns;

    auto fn = std::bind_front(&decltype(grid_)::contains, grid_);
    auto ok = std::ranges::all_of(active_piece_.indices(), fn);

    if (!ok) {
        --active_piece_.turns;
    }

    return ok;
}

bool level::turn_ccw() {
    --active_piece_.turns;

    auto fn = std::bind_front(&decltype(grid_)::contains, grid_);
    auto ok = std::ranges::all_of(active_piece_.indices(), fn);

    if (!ok) {
        ++active_piece_.turns;
    }

    return ok;
}

}

