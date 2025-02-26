#include "StateMachine.hpp"

StateMachine::StateMachine() : _currentState(sIdle)
{
    initializeMaps();
}

void StateMachine::initializeMaps()
{
    _commandToStateMap["IDLE"] = sIdle;
    _commandToStateMap["RUN"] = sRunning;
    _commandToStateMap["STOPPED"] = sStopped;
    _commandToStateMap["RESET"] = sReset;
    // Add more states here

    for (const auto &pair : _commandToStateMap)
    {
        _stateToCommandMap[pair.second] = pair.first;
    }
}

void StateMachine::setInitialState(State state)
{
    _currentState = state;
    onEnterState(state);
}

void StateMachine::handleState()
{
    switch (_currentState)
    {
    case sIdle:
        // Handle Idle state
        break;
    case sRunning:
        // Handle Running state
        transitionTo(sIdle);
        break;
    case sStopped:
        // Handle Stopped state
        break;
    // Add more states here
    case sReset:
        // Reset the arduino
        break;
    }
}

void StateMachine::transitionTo(State state)
{
    if (_currentState != state)
    {
        onExitState(_currentState);
        _currentState = state;
        onEnterState(state);
    }
}

void StateMachine::transitionTo(const String &command)
{
    State newState = mapCommandToState(command);
    transitionTo(newState);
}

StateMachine::State StateMachine::getCurrentState() const
{
    return _currentState;
}

void StateMachine::onEnterState(State state)
{
    // Serial.println("Entering " + mapStateToCommand(state) + " state");
    switch (state)
    {
    default:
        // Do nothing when state entering needs nothing
        break;
    }
}

void StateMachine::onExitState(State state)
{
    // Serial.println("Exiting " + mapStateToCommand(state) + " state");
    switch (state)
    {
    default:
        // Do nothing when state exiting needs nothing
        break;
    }
}

StateMachine::State StateMachine::mapCommandToState(const String &command)
{
    auto it = _commandToStateMap.find(command);
    if (it != _commandToStateMap.end())
    {
        return it->second;
    }
    return _currentState; // Default to current state if command is unknown
}

String StateMachine::mapStateToCommand(State state)
{
    auto it = _stateToCommandMap.find(state);
    if (it != _stateToCommandMap.end())
    {
        return it->second;
    }
    return "";
}