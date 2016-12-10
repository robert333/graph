// main.cpp
#include "debug.hpp"

#include "graph/utils.hpp"
#include "graph/Dimac.hpp"
#include "graph/matching/MatchingAlgorithms.hpp"

struct Input {
	std::string const graph_filename;
	std::string const hint_filename;
};

Input parse_input(int argc, char* argv[]);

int main (int argc, char* argv[])
{
	Input const input = parse_input(argc, argv);

	if (input.graph_filename.empty()) {
		std::cerr << "arguments needed: program_name --graph file1.dmx [--hint file2.dmx]\n";
		return 0;
	}

	graph::Dimac const dimac(input.graph_filename);

	graph::UndirectedGraph undirected_graph(dimac.num_vertices());
	graph::Matching matching(dimac.num_vertices());

	for (graph::Edge const& edge : dimac.get_edges()) {
		undirected_graph.add_edge(edge);
	}

	if (not input.hint_filename.empty()) {
		graph::Dimac const hint_dimac(input.hint_filename);

		for (graph::Edge const& edge : hint_dimac.get_edges()) {
			assert(graph::contains_edge(undirected_graph, edge));
			matching.match(edge);
		}
	}

	graph::MatchingAlgorithms matching_algorithms(undirected_graph, matching);

//	matching_algorithms.compute_greedy_matching();
//	matching_algorithms.compute_perfect_matching();
	matching_algorithms.compute_maximum_matching();

	assert(graph::is_valid_matching(undirected_graph, matching));

	graph::Dimac matching_dimac(dimac.num_vertices(), matching.compute_matching_edges());
	matching_dimac.output(std::cout);

	return 0;
}

Input parse_input(int argc, char* argv[])
{
	std::string graph_filename = "";
	std::string hint_filename = "";

	for (std::size_t i = 1; static_cast<int>(i) + 1 < argc; i += 2) {
		std::string const parameter_name = argv[i];
		std::string const parameter_value = argv[i + 1];

		if (parameter_name == "--graph") {
			graph_filename = parameter_value;
		}

		if (parameter_name == "--hint") {
			hint_filename = parameter_value;
		}
	}

	return {graph_filename, hint_filename};
}
