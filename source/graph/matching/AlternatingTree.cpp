// AlternatingTree.cpp
#include "AlternatingTree.hpp"

#include "../../debug.hpp"

namespace graph {

AlternatingTree::AlternatingTree(std::size_t const num_nodes) :
	_num_nodes(num_nodes),
	_root_node(Vertex::invalid_index()),
	_nodes(num_nodes),
	_current_iteration(0),
	_contains_node(num_nodes, 0),
	_components(num_nodes)
{
	_contained_nodes.reserve(num_nodes);
}

void AlternatingTree::reset(Vertex::Index const root_id)
{
	assert(Vertex::is_index_valid(root_id, _num_nodes));

	// deactivate all nodes
	++_current_iteration;

	// clear contained nodes without affecting reserved capacity
	_contained_nodes.clear();

	// set root node and activate it
	_root_node = root_id;
	add_node(_root_node, Vertex::invalid_index());
}

void AlternatingTree::add_node(Vertex::Index const vertex_id, Vertex::Index const incoming_vertex_id)
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(not contains_node(vertex_id));

	_contains_node[vertex_id] = _current_iteration;
	_contained_nodes.push_back(vertex_id);
	_components.reset_component(vertex_id);

	assert(is_root(vertex_id) or Vertex::is_index_valid(incoming_vertex_id, _num_nodes));
	assert(is_root(vertex_id) or contains_node(incoming_vertex_id));
	assert(is_root(vertex_id) or get_level(incoming_vertex_id) != std::numeric_limits<std::size_t>::max());
	assert(is_root(vertex_id) or get_level(incoming_vertex_id) < _num_nodes);

	Node& node = _nodes[vertex_id];
	node.level = is_root(vertex_id) ? 0 : get_level(find_base_vertex_id(incoming_vertex_id)) + 1;
	node.incoming_vertex_id = incoming_vertex_id;

	node.odd_cycle_base_vertex_id = vertex_id;
}

bool AlternatingTree::is_root(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));

	return _root_node == vertex_id;
}

bool AlternatingTree::contains_node(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));

	return _contains_node[vertex_id] == _current_iteration;
}

std::vector<Vertex::Index> AlternatingTree::get_contained_nodes() const
{
	return _contained_nodes;
}

bool AlternatingTree::is_even_node(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));

	return get_level(vertex_id) % 2 == 0;
}

std::size_t AlternatingTree::get_level(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));

	return _nodes[vertex_id].level;
}

Vertex::Index AlternatingTree::get_odd_cycle_base_vertex_id(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));

	return _nodes[vertex_id].odd_cycle_base_vertex_id;
}

Vertex::Index AlternatingTree::find_base_vertex_id(Vertex::Index const vertex_id)
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));

	return _components.find_base_vertex_id(vertex_id);
}

bool AlternatingTree::are_in_same_component(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2)
{
	return _components.are_in_same_component(vertex_id_1, vertex_id_2);
}

Vertex::Index AlternatingTree::get_incoming_vertex_id(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));
	assert(Vertex::is_index_valid(_nodes[vertex_id].incoming_vertex_id, _num_nodes));
	assert(vertex_id != _nodes[vertex_id].incoming_vertex_id);

	return _nodes[vertex_id].incoming_vertex_id;
}

void AlternatingTree::set_matching_neighbour(Vertex::Index const vertex_id, Vertex::Index const matching_neighbour){
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(Vertex::is_index_valid(matching_neighbour, _num_nodes));
	assert(contains_node(vertex_id));
	assert(contains_node(matching_neighbour));
	assert(vertex_id != matching_neighbour);

	_nodes[vertex_id].matching_neighbour = matching_neighbour;
}

Vertex::Index AlternatingTree::get_matching_neighbour(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));
	assert(_nodes[vertex_id].odd_cycle_base_vertex_id != vertex_id);

	return _nodes[vertex_id].matching_neighbour;
}

void AlternatingTree::set_incident_base_node(Vertex::Index const vertex_id, Vertex::Index const incident_base_vertex_id)
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(Vertex::is_index_valid(incident_base_vertex_id, _num_nodes));
	assert(contains_node(vertex_id));
	assert(contains_node(incident_base_vertex_id));
	assert(vertex_id != incident_base_vertex_id);

	_nodes[vertex_id].non_matching_base_vertex_id = incident_base_vertex_id;
}

void AlternatingTree::set_non_matching_edge(Vertex::Index const vertex_id, Edge const& non_matching_edge)
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));
	assert(Vertex::is_index_valid(non_matching_edge.get_tail(), _num_nodes));
	assert(Vertex::is_index_valid(non_matching_edge.get_head(), _num_nodes));
	assert(contains_node(non_matching_edge.get_tail()));
	assert(contains_node(non_matching_edge.get_head()));

	_nodes[vertex_id].non_matching_edge = non_matching_edge;
}

Vertex::Index AlternatingTree::get_incident_base_node(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));
	assert(_nodes[vertex_id].odd_cycle_base_vertex_id != vertex_id);

	return _nodes[vertex_id].non_matching_base_vertex_id;
}

Edge const& AlternatingTree::get_non_matching_edge(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
	assert(contains_node(vertex_id));
	assert(_nodes[vertex_id].odd_cycle_base_vertex_id != vertex_id);

	return _nodes[vertex_id].non_matching_edge;
}

void AlternatingTree::shrink(Vertex::Index const base_vertex_id, std::vector<Vertex::Index> const& nodes_in_odd_cycle)
{
	assert(is_even_node(base_vertex_id));

	for (Vertex::Index const vertex_id_in_odd_cycle : nodes_in_odd_cycle) {
		_components.union_components(base_vertex_id, vertex_id_in_odd_cycle, base_vertex_id);
		_nodes[vertex_id_in_odd_cycle].odd_cycle_base_vertex_id = base_vertex_id;
	}
}

//void AlternatingTree::output_tree()
//{
//	std::cout << "\nTREE\n\n";
//
//	std::cout << "root = " << _root_node << "\n";
//
//	for (Vertex::Index vertex_id = 0; vertex_id < _num_nodes; ++vertex_id) {
//		if (not contains_node(vertex_id)) {
//			continue;
//		}
//
//		output_node(vertex_id, std::to_string(vertex_id));
//
//		if (is_root(vertex_id)) {
//			continue;
//		}
//
//		Vertex::Index const& incoming_vertex_id = get_incoming_vertex_id(vertex_id);
//
//		output_edge(vertex_id, incoming_vertex_id, "incoming");
//	}
//
//	std::cout << "\n";
//}
//
//void AlternatingTree::output_node(Vertex::Index const vertex_id, std::string const& name)
//{
//	assert(Vertex::is_index_valid(vertex_id, _num_nodes));
//
//	Node const& node = _nodes[vertex_id];
//
//	std::cout << name << " = (node id = " << vertex_id
//			  << ", active = " << contains_node(vertex_id)
//			  << ", level = " << node.level
//			  << ", base node = " << _components.find_base_vertex_id(vertex_id)
//			  << ")\n";
//}
//
//void AlternatingTree::output_edge(Vertex::Index const tail_id, Vertex::Index const head_id, std::string const& name)
//{
//	std::cout << name << " "
//			  << tail_id << " (" << find_base_vertex_id(tail_id) << ")"
//			  << " ---- "
//			  << head_id << " (" << find_base_vertex_id(head_id) << ")"
//			  << "\n";
//}

} // namespace graph
