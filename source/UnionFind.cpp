// UnionFind.cpp
#include "UnionFind.hpp"

#include "debug.hpp"

UnionFind::UnionFind(std::size_t const num_sets) :
	_parents(num_sets, invalid_index()),
	_ranks(num_sets, 0)
{

}

void UnionFind::reset_set(UnionFind::Index const index)
{
	_parents[index] = index;
	_ranks[index] = 0;
}

UnionFind::Index UnionFind::find_root(Index index)
{
	Index root = index;

	while (root != _parents[root]) {
		root = _parents[root];
	}

	while (index != root) {
		Index const tmp = _parents[index];
		_parents[index] = root;
		index = tmp;
	}

	return root;
}

UnionFind::Index UnionFind::union_sets(Index const index_a, Index const index_b)
{
	Index const root_index_a = find_root(index_a);
	Index const root_index_b = find_root(index_b);

//	assert(index_a == find_root(index_a));
//	assert(index_a == find_root(index_b));
	assert(root_index_a != root_index_b);

	if (_ranks[root_index_a] < _ranks[root_index_b]) {
		_parents[root_index_a] = _parents[root_index_b];
		return root_index_b;
	} else if (_ranks[root_index_a] > _ranks[root_index_b]) {
		_parents[root_index_b] = _parents[root_index_a];
		return root_index_a;
	} else {
		_parents[root_index_b] = _parents[root_index_a];
		_ranks[root_index_a] += 1;
		return root_index_a;
	}
}

bool UnionFind::connected(UnionFind::Index const index_a, UnionFind::Index const index_b)
{
	return find_root(index_a) == find_root(index_b);
}

UnionFind::Index UnionFind::invalid_index()
{
	return std::numeric_limits<Index>::max();
}
