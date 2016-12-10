// Node.cpp
#include "Node.hpp"

namespace graph {

Node::Node()
{

}

void Node::add_incident_edge(EdgeId const edge_id)
{
	_incident_edges.push_back(edge_id);
}

void Node::add_incoming_edge(EdgeId const edge_id)
{
	_incoming_edges.push_back(edge_id);
}

void Node::add_outgoing_edge(EdgeId const edge_id)
{
	_outgoing_edges.push_back(edge_id);
}

std::size_t Node::num_incident_edges() const
{
	return _incident_edges.size();
}

std::size_t Node::num_incoming_edges() const
{
	return _incoming_edges.size();
}

std::size_t Node::num_outgoing_edges() const
{
	return _outgoing_edges.size();
}

std::vector<EdgeId> const& Node::get_incident_edges() const
{
	return _incident_edges;
}

std::vector<EdgeId> const& Node::get_incoming_edges() const
{
	return _incoming_edges;
}

std::vector<EdgeId> const& Node::get_outgoing_edges() const
{
	return _outgoing_edges;
}

} // namespace graph
