#include "ZGE/State/StateHandler.hpp"

namespace zge
{

StateHandler::StateHandler()
{
}

void StateHandler::handleEvent(const sf::Event event)
{
    if (m_stateCollection.getSize()) m_stateCollection.getTop().handleEvent(event);
}

void StateHandler::update(float dt)
{
    if (m_stateCollection.getSize()) m_stateCollection.getTop().update(dt);
}

void StateHandler::draw(sf::RenderWindow& window)
{
    if (m_stateCollection.getSize()) window.draw(m_stateCollection.getTop());
}

void StateHandler::postDraw()
{
    if (m_stateCollection.getSize()) m_stateCollection.getTop().postDraw();
}

StateCollection& StateHandler::getStateCollection()
{
    return m_stateCollection;
}

} //ZGE

