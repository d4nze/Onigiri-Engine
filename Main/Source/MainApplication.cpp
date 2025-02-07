#include "MainApplication.hpp"
#include "Core/Instance.hpp"
#include "PlayerController.hpp"
#include "PlayerRenderer.hpp"
#include "Position.hpp"
#include "imgui.h"

MainApplication::MainApplication()
	: Application(sf::VideoMode(sf::Vector2u(640, 480)))
	, m_scene(m_window)
{
    m_window.setFramerateLimit(60);
    Instance* player = m_scene.createInstance("Player");
    player->addComponent<Position>();
    player->addComponent<PlayerRenderer>();
    player->addComponent<PlayerController>();
}

void MainApplication::update()
{
    m_scene.step();
    ImGui::ShowDemoWindow();
}
