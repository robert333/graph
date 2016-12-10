// Components.hpp
#ifndef GRAPH_COMPONENT_HPP
#define GRAPH_COMPONENT_HPP

#include "../UnionFind.hpp"

#include "Vertex.hpp"

namespace graph {

class Components : public UnionFind {
public:

public:
	Components(std::size_t const num_components);

	void reset_component(Vertex::Index const vertex_id);

	Vertex::Index find_base_vertex_id(Vertex::Index const vertex_id);
	void union_components(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2, Vertex::Index const base_vertex_id);
	bool are_in_same_component(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2);

private:

private:
	std::vector<Vertex::Index> _base_vertex_ids;
};

} // namespace graph

#endif
