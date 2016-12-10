// GraphFactory.cpp
#include "GraphFactory.hpp"

#include <fstream>
#include <sstream>

namespace graph {

GraphFactory::GraphFactory()
{

}

Graph GraphFactory::read_dimac(std::string const& filename)
{
//	Logger logger(std::cout);

	std::ifstream file(filename);

	if (not file.is_open()) {
		std::cerr << "ERROR: cannot open file " << filename << "\n";
		throw;
	}
	
	std::string line;
	std::stringstream stringstream;
	
	std::string line_type;

	std::size_t num_nodes = std::numeric_limits<std::size_t>::max();
	std::size_t num_edges = std::numeric_limits<std::size_t>::max();
	
	while (std::getline(file, line)) {
		stringstream.clear();
		stringstream.str(line);

		stringstream >> line_type;

		assert(line_type != "e");

		if (line_type == "p") {
			std::string problem;

			stringstream >> problem;
			stringstream >> num_nodes;
			stringstream >> num_edges;

//			logger << line_type << " " << problem << " " << num_nodes << " " << num_edges << "\n";

			break;
		}
	}

	assert(num_nodes < std::numeric_limits<std::size_t>::max());
	assert(num_edges < std::numeric_limits<std::size_t>::max());

	Graph graph(num_nodes, num_edges, false);

	while (std::getline(file, line)) {
		stringstream.clear();
		stringstream.str(line);

		stringstream >> line_type;

		if (line_type == "e") {
			NodeId tail = invalid_node_id();
			NodeId head = invalid_node_id();

			stringstream >> tail;
			stringstream >> head;

			assert(tail != head);

			assert(tail > 0);
			assert(head > 0);

			graph.create_edge(tail - 1, head - 1);

//			logger << line_type << " " << tail << " " << head << "\n";
		}
	}

	assert(graph.num_edges() == num_edges);
	
	return graph;
}

Graph GraphFactory::input(std::string const& filename, bool const directed, bool const weighted)
{
	std::ifstream file(filename);

	if (not file.is_open()) {
		throw;
	}
	
	std::string line;

	std::getline(file, line);
	std::stringstream stringstream(line);
	
	std::size_t num_nodes;
	std::size_t num_edges;

	stringstream >> num_nodes;
	stringstream >> num_edges;
	
	Graph graph(num_nodes, num_edges, directed);
	std::vector<Weight> costs;

	while (std::getline(file, line)) {
		NodeId tail = invalid_node_id();
		NodeId head = invalid_node_id();
		Weight weight = 0;

		stringstream.clear();
		stringstream.str(line);
		
		stringstream >> tail;
		stringstream >> head;

		if (tail != head) {
			EdgeId const edge_id = graph.create_edge(tail, head);

			if (weighted) {
				stringstream >> weight;
				costs[edge_id] = weight;
			}
		} else {
			throw;
		}
	}

	return graph;
}

} // namespace graph
