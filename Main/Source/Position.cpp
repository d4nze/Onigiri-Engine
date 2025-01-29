#include "Position.hpp"

Position::Position()
	: Component()
	, m_coordinates()
{}

void Position::setX(float x) { m_coordinates.x = x; }

void Position::setY(float y) { m_coordinates.y = y; }

void Position::setCoordinates(float x, float y)
{
	m_coordinates.x = x;
	m_coordinates.y = y;
}

void Position::setCoordinates(const sf::Vector2f& coordinates) { m_coordinates = coordinates; }

float Position::getX() const { return m_coordinates.x; }

float Position::getY() const { return m_coordinates.y; }

const sf::Vector2f& Position::getCoordinates() const { return m_coordinates; }
