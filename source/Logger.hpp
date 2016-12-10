// Logger.hpp
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <ostream>

class Logger {
public:

public:
	Logger(std::ostream& ostream);

	template<typename T>
	Logger const& operator<<(T const& object) const;

private:

private:
	std::ostream& _ostream;
};

template<typename T>
Logger const& Logger::operator<<(T const& object) const
{
	_ostream << object;
	return *this;
}

#endif
