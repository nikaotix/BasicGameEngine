#pragma once
#include <SDL.h>
#include <string>
#include <iostream>

/// <summary>
/// Utility header for making interfacing with SDL less verbose
/// </summary>
inline void PrintSDLError(const std::string& msg)
{
	std::cerr << msg << " " << SDL_GetError() << std::endl;
}