// Node.hpp
#ifndef GRAPH_NODE_HPP
#define GRAPH_NODE_HPP

#include "../typedefs.hpp"

namespace graph {

class Node {
public:
	using Vector = std::vector<Node>;

public:
	Node();
	
	void add_incident_edge(EdgeId const edge_id);
	void add_incoming_edge(EdgeId const edge_id);
	void add_outgoing_edge(EdgeId const edge_id);

	std::size_t num_incident_edges() const;
	std::size_t num_incoming_edges() const;
	std::size_t num_outgoing_edges() const;

	std::vector<EdgeId> const& get_incident_edges() const;
	std::vector<EdgeId> const& get_incoming_edges() const;
	std::vector<EdgeId> const& get_outgoing_edges() const;

private:

private:
	std::vector<EdgeId> _incident_edges;
	std::vector<EdgeId> _incoming_edges;
	std::vector<EdgeId> _outgoing_edges;

	//std::vector<NodeId> _fan_in_nodes;
	//std::vector<NodeId> _fan_out_nodes;
};

} // namespace graph

#endif
