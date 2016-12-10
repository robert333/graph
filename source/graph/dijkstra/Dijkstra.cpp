// Dijkstra.cpp
#include "Dijkstra.hpp"

namespace graph {

Dijkstra::Dijkstra(Graph const& graph, std::vector<Weight> const& costs) :
	_graph(graph),
	_costs(costs)
{
	assert(graph.num_edges() == costs.size());
}

bool Dijkstra::is_reachable(NodeId const node_id) const
{
	return _reachable[node_id];
}

Weight Dijkstra::get_length(NodeId const node_id) const
{
	return _length[node_id];
}

NodeId Dijkstra::get_previous(NodeId const node_id) const
{
	return _previous[node_id];
}

void Dijkstra::compute(NodeId const node_id)
{
	std::size_t const num_nodes = _graph.num_nodes();

	_visited  .assign(num_nodes, false);
	_reachable.assign(num_nodes, false);
	_length   .assign(num_nodes, 0);
	_previous .assign(num_nodes, invalid_node_id());

	_reachable[node_id] = true;
	_length   [node_id] = 0;
	_visited  [node_id] = true;

	visit(node_id);
}

void Dijkstra::visit(NodeId const node_id)
{	
	_visited[node_id] = true;

	NodeId min_node_id = invalid_node_id();
	
	Node const& node = _graph.get_node(node_id);

	for (EdgeId const edge_id : node.get_outgoing_edges()) {
		Edge const& edge = _graph.get_edge(edge_id);
		NodeId const head_id = edge.get_head();
		
		if (_visited[head_id]) {
			continue;
		}
		
		Weight const new_length = _length[node_id] + _costs[edge_id];
		
		if (not _reachable[head_id] or _length[head_id] > new_length) {
			_reachable[head_id] = true;
			_length   [head_id] = new_length;
			_previous [head_id] = node_id;
			
			if (min_node_id == invalid_node_id() or _length[min_node_id] > new_length) {
				min_node_id = head_id;
			}
		}
	}

	if (min_node_id != invalid_node_id()) {
		visit(min_node_id);
		visit(    node_id);
	}
}

} // namespace graph
