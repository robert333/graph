// Components.cpp
#include "Components.hpp"

namespace graph {

Components::Components(std::size_t const num_components) :
	UnionFind(num_components),
	_base_vertex_ids(num_components, Vertex::invalid_index())
{
	
}

void Components::reset_component(Vertex::Index const vertex_id)
{
	reset_set(vertex_id);
	_base_vertex_ids[vertex_id] = vertex_id;
}

Vertex::Index Components::find_base_vertex_id(Vertex::Index const vertex_id)
{
	Index const root_index = find_root(vertex_id);
	return _base_vertex_ids[root_index];
}

void Components::union_components(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2, Vertex::Index const base_vertex_id)
{
	Index new_root_index = union_sets(vertex_id_1, vertex_id_2);
	_base_vertex_ids[new_root_index] = base_vertex_id;
}

bool Components::are_in_same_component(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2)
{
	return connected(vertex_id_1, vertex_id_2);
}

} // namespace graph
