// Edge.hpp
#ifndef GRAPH_EDGE_HPP
#define GRAPH_EDGE_HPP

#include "Vertex.hpp"

namespace graph {

class Edge {
public:
	using Vector = std::vector<Edge>;

public:
	Edge(Vertex::Index const tail = Vertex::invalid_index(), Vertex::Index const head = Vertex::invalid_index());

	Vertex::Index get_tail() const;
	Vertex::Index get_head() const;

	Vertex::Index get_neighbour(Vertex::Index const node_id) const;

	bool is_valid() const;

public:
	bool operator==(Edge const& other_edge) const;
	
private:

private:
	Vertex::Index /*const*/ _tail;
	Vertex::Index /*const*/ _head;
};

} // namespace graph

#endif
