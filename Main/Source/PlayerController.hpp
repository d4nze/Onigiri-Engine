#pragma once
#include "StepComponent.hpp"
#include "Position.hpp"
#include <SFML/Window/Keyboard.hpp>

class PlayerController : public StepComponent
{
public:
	PlayerController();

public:
	void create() override;
	void step() override;

private:
	Position* m_position;

	float m_moveSpeed;

	sf::Keyboard::Key m_leftkey;
	sf::Keyboard::Key m_rightkey;
	sf::Keyboard::Key m_upkey;
	sf::Keyboard::Key m_downkey;
};
