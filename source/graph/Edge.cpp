// Edge.cpp
#include "Edge.hpp"

#include <cassert>

namespace graph {

Edge::Edge(Vertex::Index const tail, Vertex::Index const head) :
	_tail(tail),
	_head(head)
{
	
}

Vertex::Index Edge::get_tail() const
{
	return _tail;
}

Vertex::Index Edge::get_head() const
{
	return _head;
}

Vertex::Index Edge::get_neighbour(Vertex::Index const node_id) const
{
	assert(node_id == get_tail() or node_id == get_head());
	return (node_id == get_tail()) ? get_head() : get_tail();
}

bool Edge::is_valid() const
{
	return get_tail() != Vertex::invalid_index()
		   and get_head() != Vertex::invalid_index()
		   and get_tail() != get_head();
}

bool Edge::operator==(Edge const& other_edge) const
{
	return get_tail() == other_edge.get_tail() and get_head() == other_edge.get_head();
}

} // namespace graph
