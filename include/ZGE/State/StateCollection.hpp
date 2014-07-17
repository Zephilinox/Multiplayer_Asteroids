#ifndef STATECOLLECTION_HPP
#define STATECOLLECTION_HPP

//STD
#include <stack>
#include <memory>

//3RD
#include <SFML/Graphics.hpp>

//SELF
namespace zge
{

class BaseState;

class StateCollection
{
public:
    StateCollection();

    template <class T>
    void push(sf::RenderWindow& window);

    void pop();

    BaseState& getTop();

    unsigned getSize();

private:
    std::stack<std::shared_ptr<BaseState>> m_states;
};

#include "ZGE/State/StateCollection.inl"

} //ZGE

#endif //STATECOLLECTION_HPP
