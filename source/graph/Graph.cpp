// Graph.cpp
#include "Graph.hpp"

namespace graph {

Graph::Graph(std::size_t const num_nodes, std::size_t const num_edges, bool const directed) :
	_directed(directed),
	_nodes(num_nodes)
{
	_edges.reserve(num_edges);
}

bool Graph::is_directed() const
{
	return _directed;
}

std::size_t Graph::num_nodes() const
{
	return _nodes.size();
}

std::size_t Graph::num_edges() const
{
	return _edges.size();
}

NodeId Graph::create_node()
{
	NodeId const node_id = num_nodes();

	_nodes.emplace_back();

	return node_id;
}

EdgeId Graph::create_edge(NodeId const tail_id, NodeId const head_id)
{
	assert(is_node_id_valid(tail_id, num_nodes()));
	assert(is_node_id_valid(head_id, num_nodes()));
	//TODO what to do with parallel edges?
//	assert(find_edge(tail_id, head_id) == invalid_edge_id());

	EdgeId const edge_id = num_edges();
	
	_edges.emplace_back(tail_id, head_id);

	if (_directed) {
		_nodes[tail_id].add_outgoing_edge(edge_id);
		_nodes[head_id].add_incoming_edge(edge_id);
	} else {
		_nodes[tail_id].add_incident_edge(edge_id);
		_nodes[head_id].add_incident_edge(edge_id);
	}

	return edge_id;
}

Node const& Graph::get_node(NodeId const node_id) const
{
	assert(is_node_id_valid(node_id, num_nodes()));
	return _nodes[node_id];
}

Edge const& Graph::get_edge(EdgeId const edge_id) const
{
	assert(is_edge_id_valid(edge_id, num_edges()));
	return _edges[edge_id];
}

Node::Vector const& Graph::get_nodes() const
{
	return _nodes;
}

Edge::Vector const& Graph::get_edges() const
{
	return _edges;
}

EdgeId Graph::find_edge(NodeId const node_a_id, NodeId const node_b_id) const
{
	Node const& node_a = get_node(node_a_id);

	for (EdgeId const edge_id : node_a.get_incident_edges()) {
		Edge const& edge = get_edge(edge_id);

		if (node_b_id == edge.get_neighbour(node_a_id)) {
			return edge_id;
		}
	}

	return invalid_edge_id();
}

bool Graph::is_valid_matching(Matching const& matching) const
{
	std::vector<bool> matched(num_nodes(), false);
	std::vector<NodeId> A;
	std::vector<NodeId> B;

	A.reserve(num_nodes() / 2);
	B.reserve(num_nodes() / 2);

	for (NodeId node_id = 0; node_id < num_nodes(); ++node_id) {
		if (matched[node_id]) {
			continue;
		}

		if (matching.is_vertex_covered(node_id)) {
			NodeId const matching_partner = matching.get_matching_partner(node_id);

			if (matched[node_id]) {
				std::cerr << "node " << node_id << " has more than one matching partner (one is "
						  << matching_partner << ")\n";
				return false;
			}

			if (matched[matching_partner]) {
				std::cerr << "node " << matching_partner << " has more than one matching partner (one is "
						  << node_id << ")\n";
				return false;
			}

			if (find_edge(node_id, matching_partner) == invalid_edge_id()) {
				std::cerr << "matched nodes are not incident (" << node_id << " and " << matching_partner << ")\n";
				return false;
			}

			matched[node_id] = true;
			matched[matching_partner] = true;

			A.push_back(node_id);
			B.push_back(matching_partner);
		}
	}

	if (not helper::is_unique(A)) {
		std::cerr << "A is not unique!\n";
		return false;
	}

	if (not helper::is_unique(B)) {
		std::cerr << "B is not unique!\n";
		return false;
	}

	if (not helper::are_disjoint(A, B)) {
		std::cerr << "A and B are not disjoint!\n";
		return false;
	}

	return true;
}

Graph Graph::create_induced_graph(Matching const& matching) const
{
	Graph graph(num_nodes(), matching.cardinality());
	std::vector<bool> matched(num_nodes(), false);

	for (NodeId node_id = 0; node_id < num_nodes(); ++node_id) {
		if (matched[node_id]) {
			continue;
		}

		if (matching.is_vertex_covered(node_id)) {
			NodeId const matching_partner = matching.get_matching_partner(node_id);

			matched[node_id] = true;
			matched[matching_partner] = true;

			graph.create_edge(node_id, matching_partner);
		}
	}

	return graph;
}

} // namespace graph
