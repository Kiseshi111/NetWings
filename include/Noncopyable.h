#pragma once

class Noncopyable
{
public:
	Noncopyable(const Noncopyable&) = delete;
	Noncopyable& operator=(const Noncopyable&) = delete;

	Noncopyable() = default;
	~Noncopyable() = default;
};