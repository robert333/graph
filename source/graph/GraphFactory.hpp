// GraphFactory.hpp
#ifndef GRAPH_GRAPH_FACTORY_HPP
#define GRAPH_GRAPH_FACTORY_HPP

#include "Graph.hpp"

namespace graph {

class GraphFactory {
public:

public:
	GraphFactory();
	
	static Graph read_dimac(std::string const& filename);

	static Graph input(std::string const& filename, bool const directed=false, bool const weighted=false);

private:

private:

};

} // namespace graph

#endif
