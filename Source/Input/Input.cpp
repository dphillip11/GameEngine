#include "input/input.h"

std::unordered_map<std::string, Input::KeyEventCallback> Input::keyCallbacks;
std::unordered_map<std::string, Input::MouseButtonEventCallback> Input::mouseButtonCallbacks;
std::unordered_map<std::string, Input::CursorPositionEventCallback> Input::cursorPositionCallbacks;