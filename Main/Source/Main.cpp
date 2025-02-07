#include "Main.hpp"
#include "Core/Instance.hpp"
#include "PlayerController.hpp"
#include "PlayerRenderer.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

std::int32_t main()
{
    Main main;
    try
    {
        main.run();
    }
    catch (std::exception exception)
    {
        return -1;
    }
    return 0;
}

Main::Main()
    : m_window(sf::VideoMode(sf::Vector2u(640, 480)), "SFML Window")
    , m_clock()
    , m_scene(m_window)
{
    m_window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(m_window))
    {
        throw std::exception();
    }
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
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
    ImGui::SFML::Update(m_window, m_clock.restart());
    ImGui::ShowDemoWindow();
    m_window.clear();
    m_scene.step();
    ImGui::SFML::Render(m_window);
    m_window.display();
}

void Main::pollEvents()
{
    while (const std::optional<sf::Event> event = m_window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(m_window, *event);
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
    }
}
