#pragma once

/// <summary>
/// ComponentID stores the GetID function that generates
/// the component IDs at runtime.
/// </summary>

extern int s_componentCounter;

template <class T>
int GetID()
{
	static int s_componentID = s_componentCounter++;
	return s_componentID;
}