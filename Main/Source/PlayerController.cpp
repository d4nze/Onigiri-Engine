#include "PlayerController.hpp"
#include "Instance.hpp"
#include "Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

PlayerController::PlayerController()
	: StepComponent(0, 1)
	, m_position(nullptr)
	, m_moveSpeed(5.f)
	, m_leftkey(sf::Keyboard::Key::Left)
	, m_rightkey(sf::Keyboard::Key::Right)
	, m_upkey(sf::Keyboard::Key::Up)
	, m_downkey(sf::Keyboard::Key::Down)
{}

void PlayerController::create()
{
	m_position = getInstance().getComponent<Position>();
	m_position->setCoordinates(getInstance().getScene().getRenderTarget().getView().getSize() / 2.f);
}

void PlayerController::step()
{
	sf::Vector2f velocity;
	if (sf::Keyboard::isKeyPressed(m_leftkey)) { velocity.x -= m_moveSpeed; }
	if (sf::Keyboard::isKeyPressed(m_rightkey)) { velocity.x += m_moveSpeed; }
	if (sf::Keyboard::isKeyPressed(m_upkey)) { velocity.y -= m_moveSpeed; }
	if (sf::Keyboard::isKeyPressed(m_downkey)) { velocity.y += m_moveSpeed; }
	m_position->setCoordinates(m_position->getCoordinates() + velocity);
}
