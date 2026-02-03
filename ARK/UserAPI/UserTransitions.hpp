#pragma once
class StatesManager;

void UserEvaluateTransitions(StatesManager& flightManager);
void UserOnStateEnter(int stateEnum);
void UserOnStateExit(int stateEnum);
