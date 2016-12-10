// vector_helper.hpp
#ifndef VECTOR_HELPER_HPP
#define VECTOR_HELPER_HPP

#include <vector>
#include <deque>
#include <algorithm>

namespace helper {

template<typename T>
bool is_unique(std::vector<T> const& vector)
{
	std::vector<T> vector_copy = vector;
	std::sort(vector_copy.begin(), vector_copy.end());
	return std::unique(vector_copy.begin(), vector_copy.end()) == vector_copy.end();
}

template<typename T>
bool is_unique(std::deque<T> const& deque)
{
	std::deque<T> deque_copy = deque;
	std::sort(deque_copy.begin(), deque_copy.end());
	return std::unique(deque_copy.begin(), deque_copy.end()) == deque_copy.end();
}

template<typename T>
bool contains(std::vector<T> const& vector, T const& object)
{
	return std::find(vector.begin(), vector.end(), object) != vector.end();
}

template<typename T>
void append(std::vector<T>& vector, std::vector<T> const& vector_appending)
{
	vector.insert(vector.end(), vector_appending.begin(), vector_appending.end());
}

template<typename T>
bool are_disjoint(std::vector<T> const& vector_a, std::vector<T> const& vector_b)
{
	std::vector<T> vector_copy = vector_a;
	append(vector_copy, vector_b);
	return is_unique(vector_copy);
}

} // namespace helper

#endif
