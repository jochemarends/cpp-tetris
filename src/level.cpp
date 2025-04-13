#include "level.h"

namespace tetris {

level::level(sf::Vector2f top_left, std::size_t tile_size)
    :grid_{top_left, tile_size} {}

} 

}

