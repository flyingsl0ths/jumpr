#include "common.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

s32 main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "Jumpr",
                            sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
