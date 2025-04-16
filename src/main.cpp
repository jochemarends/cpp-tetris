#include <color.h>
#include <level.h>
#include <tetromino.h>
#include <print>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <game.h>
#include <grid.h>

int main() {
    sf::VideoMode video_mode{sf::Vector2u{tetris::game::width, tetris::game::height}};
    sf::RenderWindow window{video_mode, "tetris"};

    // prevent SFML from writing errors to the terminal 
    sf::err().rdbuf(nullptr);

    // number of ticks per second
    constexpr float tick_rate{4.0f};
    sf::Clock clock{};

    constexpr sf::Vector2f top_left{0.0f, 0.0f};
    constexpr std::size_t tile_size{40uz};

    tetris::level level{top_left, tile_size};

    while (window.isOpen()) {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        if (clock.getElapsedTime().asSeconds() > (1.0f / tick_rate)) {
            level.tick();
            clock.restart();
        }

        window.draw(level);
        window.display();
    }
}

