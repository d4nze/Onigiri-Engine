#include "Environment.hpp"

Environment::Environment(sf::RenderTarget& renderTarget)
    : m_renderTarget(renderTarget)
{}

sf::RenderTarget& Environment::getRenderTarget()
{
    return m_renderTarget;
}

const sf::RenderTarget& Environment::getRenderTarget() const
{
    return m_renderTarget;
}
