// Dijkstra.hpp
#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "../Graph.hpp"

namespace graph {

class Dijkstra {
public:

public:
	Dijkstra(Graph const& graph, std::vector<Weight> const& costs);

	bool is_reachable(NodeId const node_id) const;

	Weight get_length(NodeId const node_id) const;

	NodeId get_previous(NodeId const node_id) const;

	void compute(NodeId const node_id);

private:
	void visit(NodeId const node_id);

private:
	Graph const& _graph;
	std::vector<Weight> const& _costs;

	std::vector<bool> _reachable;
	std::vector<Weight> _length;
	std::vector<NodeId> _previous;
	std::vector<bool> _visited;
};

} // namespace graph

#endif
