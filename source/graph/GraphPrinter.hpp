// GraphPrinter.hpp
#ifndef GRAPH_GRAPH_PRINTER_HPP
#define GRAPH_GRAPH_PRINTER_HPP

#include <string>

#include "Graph.hpp"
#include "UndirectedGraph.hpp"

namespace graph {

class GraphPrinter {
public:

public:
	GraphPrinter();
	
	static void output(Graph const& graph);
	static void output(std::string const& filename, Graph const& graph);

	static void output_dimac(Graph const& graph);
	static void output_dimac(Graph const& graph, std::string const& filename);

	static void output_dimac(Graph const& graph, Matching const& matching, std::string const& filename = "");

	static void output_dimac(UndirectedGraph const& undirected_graph,
							 Matching const& matching,
							 std::string const& filename = "");

private:
	static void output(std::ostream& ostream, Graph const& graph);
	static void output_edge(std::ostream& ostream, Edge const& edge, bool const directed = true, bool const weighted = true);

	static void output_dimac(std::ostream& ostream, Graph const& graph);
	static void output_dimac(std::ostream& ostream, Graph const& graph, Matching const& matching);
	static void output_dimac(std::ostream& ostream, UndirectedGraph const& undirected_graph, Matching const& matching);

private:

};

} // namespace graph

#endif
