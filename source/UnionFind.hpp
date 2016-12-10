// UnionFind.hpp
#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <vector>
#include <limits>

class UnionFind {
public:
	using Index = std::size_t;
	using Rank = std::size_t;

public:
	UnionFind(std::size_t const num_sets);

	void reset_set(Index const index);

	Index find_root(Index index);

	Index union_sets(Index const index_a, Index const index_b);

	bool connected(Index const index_a, Index const index_b);

private:
	static Index invalid_index();

private:
	std::vector<Index> _parents;
	std::vector<Rank> _ranks;
};

#endif
