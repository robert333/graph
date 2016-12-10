// test_matching_instances.cpp
#include "catch/catch.hpp"

#include "../debug.hpp"

#include "../graph/utils.hpp"
#include "../graph/Dimac.hpp"
#include "../graph/matching/MatchingAlgorithms.hpp"

//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/max_cardinality_matching.hpp>

TEST_CASE("Matching Instances", "[matching instances]") {
	struct Instance {
		std::string name;
		std::size_t max_cardinality;
	};

	std::vector<Instance> instances = {
		{"K2", 1},
		{"K3", 1},
		{"K4", 2},
		{"P3", 2},
		{"simple", 2},
		{"peterson", 5},
		{"queen4_4", 8},
		{"queen5_5", 12},
		{"queen6_6", 18},
		{"queen7_7", 24},
		{"queen8_8", 32},
		{"queen9_9", 40},
		{"queen10_10", 50},
		{"queen11_11", 60},
		{"queen16_16", 128},
		{"queen27_27", 364},
		{"xqf131", 64},
		{"pma343", 171},
		{"lu980", 490},
		{"pbd984", 492},
		{"fixed", 500},
		{"ei8246", 4123},
		{"ar9152", 4349},
		{"gr9882", 4931},
		{"ch71009", 35025},
		{"USA-road-d.FLA", 507967},
		{"USA-road-d.USA", 11325669}
	};

	std::string const instances_path = "../instances/matching/";

	for (Instance const& instance : instances) {
		std::cout << "Compute instance " << instance.name << "...\n";

		graph::Dimac const dimac_graph(instances_path + "graphs/" + instance.name + ".dmx");
		graph::Dimac const dimac_hint(instances_path + "hint_matchings/" + instance.name + "_matching_maximal.dmx");

		graph::UndirectedGraph undirected_graph(dimac_graph.num_vertices());
		graph::Matching matching(dimac_graph.num_vertices());

		for (graph::Edge const& edge : dimac_graph.get_edges()) {
			undirected_graph.add_edge(edge);
		}

		for (graph::Edge const& edge : dimac_hint.get_edges()) {
			assert(graph::contains_edge(undirected_graph, edge));
			matching.match(edge);
		}

		graph::MatchingAlgorithms matching_algorithms(undirected_graph, matching);
		matching_algorithms.compute_maximum_matching();

		assert(graph::is_valid_matching(undirected_graph, matching));

		graph::Dimac matching_dimac(dimac_graph.num_vertices(), matching.compute_matching_edges());
		matching_dimac.output(instances_path + "maximum_matchings/" + instance.name + "_matching_maximum.dmx");

		REQUIRE(matching.cardinality() == instance.max_cardinality);

		// verify results with boost algorithm
//		using boost_graph_type = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
//		boost_graph_type boost_graph(graph.num_nodes());
//
//		for (Edge const& edge : graph.get_edges()) {
//			boost::add_edge(edge.get_tail(), edge.get_head(), boost_graph);
//		}
//
//		std::vector<boost::graph_traits<boost_graph_type>::vertex_descriptor> boost_mate(graph.num_nodes());
//
//		std::cout << "boost computing maximum matching...\n";
//		REQUIRE(boost::checked_edmonds_maximum_cardinality_matching(boost_graph, &boost_mate[0]));
////		boost::edmonds_maximum_cardinality_matching(boost_graph, &boost_mate[0]);
//		std::cout << "boost computing maximum matching finished\n\n";
//		REQUIRE(boost::matching_size(boost_graph, &boost_mate[0]) == instance.max_cardinality);
//		REQUIRE(boost::matching_size(boost_graph, &boost_mate[0]) == matching.cardinality());
	}
}
