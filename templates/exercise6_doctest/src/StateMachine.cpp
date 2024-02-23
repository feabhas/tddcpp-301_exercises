// StateMachine.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "StateMachine.h"

#include "Closed.h"
#include "Open.h"

#include <exception>
#include <typeinfo>

StateMachine* StateMachine::initialise()
{
  return new Closed;
}

void StateMachine::terminate(StateMachine* state)
{
  delete state;
}

StateMachine* StateMachine::no_transition()
{
  return this;
}

StateMachine* StateMachine::illegal_transition()
{
  throw std::domain_error("illegal transition");
  return this;
}
bool StateMachine::doorIsClosed(StateMachine* current_state)
{
  return (typeid(*current_state) == typeid(Closed));
}

bool StateMachine::doorIsOpen(StateMachine* current_state)
{
  return (typeid(*current_state) == typeid(Open));
}
