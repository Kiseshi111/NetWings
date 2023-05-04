#include <time.h>

#include "../include/TimeStamp.h"

TimeStamp::TimeStamp() : thisTime(0)
{
}

TimeStamp::TimeStamp(int64_t times)
	: thisTime(times)
{
}

TimeStamp TimeStamp::now()
{
	return TimeStamp(time(NULL));
}

std::string TimeStamp::toString() const
{
	char buf[128] = { 0 };
	tm* tm_time = localtime(&thisTime);
    snprintf(buf, 128, "%4d/%02d/%02d %02d:%02d:%02d",
        tm_time->tm_year + 1900,
        tm_time->tm_mon + 1,
        tm_time->tm_mday,
        tm_time->tm_hour,
        tm_time->tm_min,
        tm_time->tm_sec);
    return buf;
}