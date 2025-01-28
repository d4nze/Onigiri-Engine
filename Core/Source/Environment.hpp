#pragma once
#include "CoreAPI.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class CORE_API Environment
{
private:
	Environment(sf::RenderTarget& renderTarget);

public:
	sf::RenderTarget& getRenderTarget();
	const sf::RenderTarget& getRenderTarget() const;

private:
	sf::RenderTarget& m_renderTarget;

	friend class Main;
};
