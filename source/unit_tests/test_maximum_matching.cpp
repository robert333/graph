// test_maximum_matching.cpp
#include "catch/catch.hpp"

#include "../graph/matching/MatchingAlgorithms.hpp"

TEST_CASE("Computing Maximum Matchings (Test 1)", "[maximum matching]" ) {
	graph::UndirectedGraph undirected_graph(12);

	undirected_graph.add_edge(0, 4);
	undirected_graph.add_edge(0, 5);
	undirected_graph.add_edge(1, 6);
	undirected_graph.add_edge(1, 7);
	undirected_graph.add_edge(2, 8);
	undirected_graph.add_edge(2, 9);
	undirected_graph.add_edge(3, 10);
	undirected_graph.add_edge(3, 11);

	graph::Matching matching(undirected_graph.num_vertices());

	graph::MatchingAlgorithms matching_algorithms(undirected_graph, matching);
	matching_algorithms.compute_perfect_matching();

	REQUIRE(matching.is_vertex_covered(0) == true);
	REQUIRE(matching.is_vertex_covered(1) == true);
	REQUIRE(matching.is_vertex_covered(2) == true);
	REQUIRE(matching.is_vertex_covered(3) == true);
	REQUIRE(matching.is_vertex_covered(4) == true);
	REQUIRE(matching.is_vertex_covered(5) == false);
	REQUIRE(matching.is_vertex_covered(6) == true);
	REQUIRE(matching.is_vertex_covered(7) == false);
	REQUIRE(matching.is_vertex_covered(8) == true);
	REQUIRE(matching.is_vertex_covered(9) == false);
	REQUIRE(matching.is_vertex_covered(10) == true);
	REQUIRE(matching.is_vertex_covered(11) == false);
}