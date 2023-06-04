#pragma once
#include <string>
#include <filesystem>

template <typename T>
std::string NameToString(std::string dir, T name, std::string ext)
{
	//make the full file path
	std::filesystem::path path = std::filesystem::current_path();
	path.append(dir);
	path.append(static_cast<std::string>(name).append(ext.c_str()));
	return path.u8string(); //forcing u8 string because SDL2?
}