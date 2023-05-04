#pragma once

#include <string>
#include <iostream>

class TimeStamp
{
public:
	TimeStamp();
	explicit TimeStamp(int64_t thisTime);
	
private:
	int64_t thisTime;

public:
	static TimeStamp now();
	std::string toString() const;
};