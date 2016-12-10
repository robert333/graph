// Dimac.hpp
#ifndef DIMAC_HPP
#define DIMAC_HPP

#include <string>

#include "Edge.hpp"

namespace graph {

class Dimac {
public:

public:
	Dimac(std::size_t const num_vertices, Edge::Vector const& edges);
	Dimac(std::string const& dimac_filename);

	std::size_t num_vertices() const;
	Edge::Vector const& get_edges() const;

	void output(std::string const& filename);
	void output(std::ostream& ostream);

private:
	void read_dimac_file(std::string const& dimac_filename);

private:
	std::size_t _num_vertices;
	Edge::Vector _edges;
};

} // namespace graph

#endif
