// typedefs.cpp
#include "typedefs.hpp"

NodeId invalid_node_id()
{
	return std::numeric_limits<NodeId>::max();
}

EdgeId invalid_edge_id()
{
	return std::numeric_limits<EdgeId>::max();
}

bool is_node_id_valid(NodeId const node_id, std::size_t const num_nodes)
{
	assert(node_id != invalid_node_id());
//	assert(node_id >= 0);
	assert(node_id < num_nodes);
	return node_id != invalid_node_id() /*and node_id >= 0*/ and node_id < num_nodes;
}

bool is_edge_id_valid(EdgeId const edge_id, std::size_t const num_edges)
{
	assert(edge_id != invalid_edge_id());
//	assert(edge_id >= 0);
	assert(edge_id < num_edges);
	return edge_id != invalid_edge_id() /*and edge_id >= 0*/ and edge_id < num_edges;
}
