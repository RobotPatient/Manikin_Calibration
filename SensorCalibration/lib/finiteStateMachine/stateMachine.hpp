#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <Arduino.h>
#include <map>

class StateMachine
{
public:
    enum State
    {
        sIdle,
        sRunning,
        sStopped,
        sReset,
        // Add more states here
    };

    StateMachine();
    void setInitialState(State state);
    void handleState();
    void transitionTo(State state);
    void transitionTo(const String &command);
    State getCurrentState() const;

private:
    State _currentState;
    void onEnterState(State state);
    void onExitState(State state);
    State mapCommandToState(const String &command);
    String mapStateToCommand(State state);

    std::map<String, State> _commandToStateMap;
    std::map<State, String> _stateToCommandMap;
    void initializeMaps();
};

#endif // STATEMACHINE_HPP