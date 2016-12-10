// GraphPrinter.cpp
#include "GraphPrinter.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace graph {

GraphPrinter::GraphPrinter()
{

}

void GraphPrinter::output(Graph const& graph)
{
	output(std::cout, graph);
}

void GraphPrinter::output(std::string const& filename, Graph const& graph)
{
	std::ofstream file(filename);
	assert(file.is_open());
	output(file, graph);
	file.close();
}

void GraphPrinter::output_dimac(Graph const &graph) {
	output_dimac(std::cout, graph);
}

void GraphPrinter::output_dimac(Graph const& graph, std::string const& filename)
{
	std::ofstream file(filename);

	if (not file.is_open()) {
		throw;
	}

	output_dimac(file, graph);

	file.close();
}

void GraphPrinter::output_dimac(Graph const& graph, Matching const& matching, std::string const& filename)
{
	if (filename.empty()) {
		output_dimac(std::cout, graph, matching);
	} else {
		std::ofstream file(filename);

		if (not file.is_open()) {
			throw;
		}

		output_dimac(file, graph, matching);

		file.close();
	}
}

void GraphPrinter::output_dimac(UndirectedGraph const& undirected_graph,
								Matching const& matching,
								std::string const& filename)
{
	if (filename.empty()) {
		output_dimac(std::cout, undirected_graph, matching);
	} else {
		std::ofstream file(filename);

		if (not file.is_open()) {
			throw;
		}

		output_dimac(file, undirected_graph, matching);

		file.close();
	}
}

void GraphPrinter::output(std::ostream& ostream, Graph const& graph)
{
	std::size_t const num_nodes = graph.num_nodes();
	std::size_t const num_edges = graph.num_edges();
	
	bool const directed = graph.is_directed();
	bool const weighted = false;//graph.is_weighted();

	if (directed) {
		ostream << "Directed ";
	}
	
	if (weighted) {
		ostream << "Weighted ";
	}
	
	ostream << "Graph with " << num_nodes << " nodes and " << num_edges << " edges\n\n";

	for (NodeId node_id = 0; node_id < num_nodes; ++node_id) {
		Node const& node = graph.get_node(node_id);

		if (directed) {
			ostream << "Node " << node_id << " with "
				    << node.num_incoming_edges() << " incoming edges and "
				    << node.num_outgoing_edges() << " outgoing edges\n";

			for (EdgeId const edge_id : node.get_incoming_edges()) {
				Edge const& edge = graph.get_edge(edge_id);
				output_edge(ostream, edge, directed, weighted);
			}

			for (EdgeId const edge_id : node.get_outgoing_edges()) {
				Edge const& edge = graph.get_edge(edge_id);
				output_edge(ostream, edge, directed, weighted);
			}
		} else {
			ostream << "Node " << node_id << " with " << node.num_incident_edges() << " incident edges\n";

			for (EdgeId const edge_id : node.get_incident_edges()) {
				Edge const& edge = graph.get_edge(edge_id);
				output_edge(ostream, edge, directed, weighted);
			}
		}

		ostream << "\n";
	}
	
	ostream << "Edges\n";
	
	for (EdgeId edge_id = 0; edge_id < num_edges; ++edge_id) {
		Edge const& edge = graph.get_edge(edge_id);
		output_edge(ostream, edge, directed, weighted);
	}
}

void GraphPrinter::output_edge(std::ostream& ostream, Edge const& edge, bool const directed, bool const weighted)
{
	ostream << edge.get_tail() << " --";
	
	if (weighted) {
//		ostream << "( " << edge.get_weight() << " )";
	}
	
	ostream << "--";
	
	if (directed) {
		ostream << ">";
	}
	
	ostream << " " << edge.get_head() << "\n";
}

void GraphPrinter::output_dimac(std::ostream& ostream, Graph const& graph) {
	ostream << "p edge " << graph.num_nodes() << " " << graph.num_edges() << "\n";

	for (Edge const& edge : graph.get_edges()) {
		ostream << "e " << edge.get_tail() + 1 << " " << edge.get_head() + 1 << "\n";
	}
}

void GraphPrinter::output_dimac(std::ostream& ostream, Graph const& graph, Matching const& matching)
{
	ostream << "p edge " << graph.num_nodes() << " " << matching.cardinality() << "\n";

	std::vector<bool> processed(graph.num_nodes(), false);

	for (NodeId node_id = 0; node_id < graph.num_nodes(); ++node_id) {
		if (processed[node_id]) {
			continue;
		}

		if (matching.is_vertex_covered(node_id)) {
			NodeId const matching_partner = matching.get_matching_partner(node_id);
			ostream << "e " << node_id + 1 << " " << matching_partner + 1 << "\n";
			processed[node_id] = true;
			processed[matching_partner] = true;
		}
	}
}

void GraphPrinter::output_dimac(std::ostream& ostream,
								UndirectedGraph const& undirected_graph,
								Matching const& matching)
{
	ostream << "p edge " << undirected_graph.num_vertices() << " " << matching.cardinality() << "\n";

	std::vector<bool> processed(undirected_graph.num_vertices(), false);

	for (NodeId node_id = 0; node_id < undirected_graph.num_vertices(); ++node_id) {
		if (processed[node_id]) {
			continue;
		}

		if (matching.is_vertex_covered(node_id)) {
			NodeId const matching_partner = matching.get_matching_partner(node_id);
			ostream << "e " << node_id + 1 << " " << matching_partner + 1 << "\n";
			processed[node_id] = true;
			processed[matching_partner] = true;
		}
	}
}

} // namespace graph
