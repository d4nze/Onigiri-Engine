#pragma once
#include "Core/StepComponent.hpp"
#include "Position.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class PlayerRenderer : public StepComponent
{
public:
	PlayerRenderer();

public:
	void create() override;
	void step() override;

private:
	Position* m_position;
	sf::RenderTarget* m_renderTarget;
	sf::RectangleShape m_rectangle;
};
