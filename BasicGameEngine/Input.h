#pragma once

#include <vector>
#include <cstdint>

enum InputType {
	KEYBOARD,
	INVALID_INPUTTYPE,
};

typedef struct
{
	InputType type;
	size_t inputMapping; //TODO: define this - should be some map from keyboard/joystick/mouse to axis/buttons.
	size_t numAxes;
	size_t numButtons;
	std::vector<float> Axes;
	std::vector<bool> buttonPressed;
	std::vector<bool> buttonReleased;
	std::vector<bool> buttonState;
} Input;