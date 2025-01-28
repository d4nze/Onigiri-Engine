#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

std::int32_t main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(640, 480)), "SFML Window");
    sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.f));
    rectangle.setPosition(sf::Vector2f(320.f, 240.f) - rectangle.getSize() / 2.f);
    rectangle.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
