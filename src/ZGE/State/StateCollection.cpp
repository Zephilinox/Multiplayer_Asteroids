#include "ZGE/State/StateCollection.hpp"

//STD
#include <iostream>
#include <cassert>

namespace zge
{

StateCollection::StateCollection()
{
}

void StateCollection::pop()
{
    m_states.pop();
}

BaseState& StateCollection::getTop()
{
    assert(m_states.size());
    return *m_states.top();
}

unsigned StateCollection::getSize()
{
    return m_states.size();
}

} //ZGE
