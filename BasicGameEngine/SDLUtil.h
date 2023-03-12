#pragma once
#include <SDL.h>
#include <string>
#include <iostream>

inline void PrintSDLError(const std::string& msg)
{
	std::cerr << msg << " " << SDL_GetError() << std::endl;
}