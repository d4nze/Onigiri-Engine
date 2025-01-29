#include "PlayerRenderer.hpp"
#include "Instance.hpp"
#include "Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

PlayerRenderer::PlayerRenderer()
	: StepComponent()
	, m_position(nullptr)
	, m_renderTarget(nullptr)
	, m_rectangle(sf::Vector2f(128.f, 128.f))
{
	m_rectangle.setOrigin(m_rectangle.getSize() / 2.f);
	m_rectangle.setFillColor(sf::Color::Green);
}

void PlayerRenderer::create()
{
	m_position = getInstance().getComponent<Position>();
	m_renderTarget = &getInstance().getScene().getRenderTarget();
}

void PlayerRenderer::step()
{
	m_rectangle.setPosition(m_position->getCoordinates());
	m_renderTarget->draw(m_rectangle);
}
