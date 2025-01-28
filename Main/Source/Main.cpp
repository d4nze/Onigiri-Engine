#include "Main.hpp"

std::int32_t main()
{
    Main main;
    main.run();
    return 0;
}

Main::Main()
    : m_window(sf::VideoMode(sf::Vector2u(640, 480)), "SFML Window")
    , m_environment(m_window)
    , m_script(new Script)
{
    m_script->m_environment = &m_environment;
    m_script->create();
}

void Main::run()
{
    m_script->step();
    while (m_window.isOpen()) { loop(); }
}

void Main::loop()
{
    pollEvents();
    m_window.clear();
    m_script->step();
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
