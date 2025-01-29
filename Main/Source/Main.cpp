#include "Main.hpp"
#include "Instance.hpp"
#include "PlayerController.hpp"
#include "PlayerRenderer.hpp"

std::int32_t main()
{
    Main main;
    main.run();
    return 0;
}

Main::Main()
    : m_window(sf::VideoMode(sf::Vector2u(640, 480)), "SFML Window")
    , m_scene(m_window)
{
    m_window.setFramerateLimit(60);
    initScene();
}

void Main::run()
{
    while (m_window.isOpen()) { loop(); }
}

void Main::initScene()
{
    Instance* player = m_scene.createInstance("Player");
    player->addComponent<Position>();
    player->addComponent<PlayerRenderer>();
    player->addComponent<PlayerController>();
}

void Main::loop()
{
    pollEvents();
    m_window.clear();
    m_scene.step();
    m_window.display();
}

void Main::pollEvents()
{
    while (const std::optional<sf::Event> event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
    }
}
