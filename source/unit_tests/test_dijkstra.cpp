// test_dijkstra.cpp
#include "catch/catch.hpp"

#include "../graph/Graph.hpp"
#include "../graph/GraphPrinter.hpp"
#include "../graph/dijkstra/Dijkstra.hpp"

#include <iostream>

TEST_CASE("Computing Shortest Paths width Dijkstra Algorithm", "[dijkstra]" ) {
	graph::Graph graph(4, 6, true);
	
	graph.create_edge(0, 1);
	graph.create_edge(0, 2);
	graph.create_edge(1, 2);
	graph.create_edge(2, 1);
	graph.create_edge(1, 3);
	graph.create_edge(2, 3);

	graph::GraphPrinter::output(graph);

	std::vector<Weight> const costs = {1, 2, 0, 0, 3, 2};

	graph::Dijkstra dijkstra(graph, costs);
	
	dijkstra.compute(0);

	for (NodeId node_id = 0; node_id < graph.num_nodes(); ++node_id) {
		std::cout << node_id << ' ' << dijkstra.is_reachable(node_id)
		                     << ' ' << dijkstra.get_length  (node_id)
		                     << ' ' << dijkstra.get_previous(node_id) << '\n';
	}
	
	REQUIRE(dijkstra.is_reachable(0) == true);
	REQUIRE(dijkstra.is_reachable(1) == true);
	REQUIRE(dijkstra.is_reachable(2) == true);
	REQUIRE(dijkstra.is_reachable(3) == true);
	
	REQUIRE(dijkstra.get_length(0) == 0);
	REQUIRE(dijkstra.get_length(1) == 1);
	REQUIRE(dijkstra.get_length(2) == 1);
	REQUIRE(dijkstra.get_length(3) == 3);
	
	REQUIRE(dijkstra.get_previous(0) == invalid_node_id());
	REQUIRE(dijkstra.get_previous(1) == 0);
	REQUIRE(dijkstra.get_previous(2) == 1);
	REQUIRE(dijkstra.get_previous(3) == 2);
}
