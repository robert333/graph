// Graph.hpp
#ifndef GRAPH_GRAPH_HPP
#define GRAPH_GRAPH_HPP

#include "Node.hpp"
#include "Edge.hpp"

#include "matching/Matching.hpp"

namespace graph {

class Graph {
public:

public:
	Graph(std::size_t const num_nodes, std::size_t const num_edges, bool const directed = false);

	bool is_directed() const;

	std::size_t num_nodes() const;
	std::size_t num_edges() const;

	NodeId create_node();
	EdgeId create_edge(NodeId const tail_id, NodeId const head_id);

	Node const& get_node(NodeId const node_id) const;
	Edge const& get_edge(EdgeId const edge_id) const;

	Node::Vector const& get_nodes() const;
	Edge::Vector const& get_edges() const;

	EdgeId find_edge(NodeId const node_a_id, NodeId const node_b_id) const;

	bool is_valid_matching(Matching const& matching) const;

	Graph create_induced_graph(Matching const& matching) const;

private:

private:
	bool const _directed;

	Node::Vector _nodes;
	Edge::Vector _edges;
};

} // namespace graph

#endif
