#pragma once
#include "Component.hpp"
#include <SFML/System/Vector2.hpp>

class Position : public Component
{
public:
	Position();

public:
	void setX(float x);
	void setY(float y);
	void setCoordinates(float x, float y);
	void setCoordinates(const sf::Vector2f& coordinates);

	float getX() const;
	float getY() const;
	const sf::Vector2f& getCoordinates() const;

private:
	sf::Vector2f m_coordinates;
};
