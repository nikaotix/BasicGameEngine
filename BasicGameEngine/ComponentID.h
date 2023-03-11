#pragma once

extern int s_componentCounter;

template <class T>
int GetID()
{
	static int s_componentID = s_componentCounter++;
	return s_componentID;
}