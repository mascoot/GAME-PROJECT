#include "KeyBinder.h"


bool InputManager::KeyPressed(unsigned short key)
{
    return GetAsyncKeyState(key) < 0 ? pressed[key] = true : false;
}

bool InputManager::KeyToggled(unsigned short key)
{
    return (pressed.find(key) == pressed.end()) ? true : false;
}

void InputManager::Update()
{
}