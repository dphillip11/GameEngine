#pragma once

template <typename DerivedClass>
class Singleton
{
public:
	// Lazy instantiation
	static DerivedClass& GetInstance()
	{
		static DerivedClass instance;
		return instance;
	}

protected:
	Singleton() = default;
	~Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};
