// test_perfect_matching.cpp
#include "catch/catch.hpp"

#include "../graph/Graph.hpp"
#include "../graph/GraphPrinter.hpp"
#include "../graph/matching/MatchingAlgorithms.hpp"

#include <iostream>

TEST_CASE("Computing Perfect Matchings (Test 1)", "[perfect matching]" ) {
	graph::UndirectedGraph undirected_graph(4);

	undirected_graph.add_edge(0, 2);
	undirected_graph.add_edge(0, 1);
	undirected_graph.add_edge(2, 1);
	undirected_graph.add_edge(2, 3);

	graph::Matching matching(undirected_graph.num_vertices());

	graph::MatchingAlgorithms matching_algorithms(undirected_graph, matching);
	matching_algorithms.compute_perfect_matching();
	
	REQUIRE(matching.is_vertex_covered(0) == true);
	REQUIRE(matching.is_vertex_covered(1) == true);
	REQUIRE(matching.is_vertex_covered(2) == true);
	REQUIRE(matching.is_vertex_covered(3) == true);
}

TEST_CASE("Computing Perfect Matchings (Test 2)", "[perfect matching]" ) {
	graph::UndirectedGraph undirected_graph(4);

	undirected_graph.add_edge(0, 2);
	undirected_graph.add_edge(0, 1);
	undirected_graph.add_edge(2, 1);
	undirected_graph.add_edge(0, 3);

	graph::Matching matching(undirected_graph.num_vertices());

	graph::MatchingAlgorithms matching_algorithms(undirected_graph, matching);
	matching_algorithms.compute_perfect_matching();

	REQUIRE(matching.is_vertex_covered(0) == true);
	REQUIRE(matching.is_vertex_covered(1) == true);
	REQUIRE(matching.is_vertex_covered(2) == true);
	REQUIRE(matching.is_vertex_covered(3) == true);
}

TEST_CASE("Computing Perfect Matchings (Test 3)", "[perfect matching]" ) {
	graph::UndirectedGraph undirected_graph(4);

	undirected_graph.add_edge(0, 2);
	undirected_graph.add_edge(0, 1);
	undirected_graph.add_edge(2, 1);
	undirected_graph.add_edge(2, 3);
	undirected_graph.add_edge(0, 3);

	graph::Matching matching(undirected_graph.num_vertices());

	graph::MatchingAlgorithms matching_algorithms(undirected_graph, matching);
	matching_algorithms.compute_perfect_matching();

	REQUIRE(matching.is_vertex_covered(0) == true);
	REQUIRE(matching.is_vertex_covered(1) == true);
	REQUIRE(matching.is_vertex_covered(2) == true);
	REQUIRE(matching.is_vertex_covered(3) == true);
}

TEST_CASE("Computing Perfect Matchings (Test 4)", "[perfect matching]" ) {
	graph::UndirectedGraph undirected_graph(10);

	undirected_graph.add_edge(0, 2);
	undirected_graph.add_edge(0, 1);
	undirected_graph.add_edge(2, 1);
	undirected_graph.add_edge(2, 3);
	undirected_graph.add_edge(0, 3);
	undirected_graph.add_edge(1, 3);
	undirected_graph.add_edge(4, 5);
	undirected_graph.add_edge(6, 7);
	undirected_graph.add_edge(4, 6);
	undirected_graph.add_edge(4, 0);
	undirected_graph.add_edge(2, 7);
	undirected_graph.add_edge(3, 6);
	undirected_graph.add_edge(4, 3);
	undirected_graph.add_edge(5, 3);
	undirected_graph.add_edge(7, 5);
	undirected_graph.add_edge(8, 7);
	undirected_graph.add_edge(9, 6);
	undirected_graph.add_edge(9, 0);

	graph::Matching matching(undirected_graph.num_vertices());

	graph::MatchingAlgorithms matching_algorithms(undirected_graph, matching);
	matching_algorithms.compute_perfect_matching();
}
