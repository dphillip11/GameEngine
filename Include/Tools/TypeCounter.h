#pragma once

class typeCounter
{
public:
	static int counter;
};

template <typename T>
int GetTypeID()
{
	static int typeID = typeCounter::counter++;
	return typeID;
}

template <typename T>
int GetTypeID(T t)
{
	return GetTypeID<T>();
}