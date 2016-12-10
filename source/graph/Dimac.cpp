// Dimac.cpp
#include "Dimac.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

namespace graph {

Dimac::Dimac(std::size_t const num_vertices, Edge::Vector const& edges) :
	_num_vertices(num_vertices),
	_edges(edges)
{

}

Dimac::Dimac(std::string const& dimac_filename)
{
	read_dimac_file(dimac_filename);
}

std::size_t Dimac::num_vertices() const
{
	return _num_vertices;
}

Edge::Vector const& Dimac::get_edges() const
{
	return _edges;
}

void Dimac::output(std::string const& filename)
{
	std::ofstream file(filename);

	if (not file.is_open()) {
		throw;
	}

	output(file);

	file.close();
}

void Dimac::output(std::ostream& ostream)
{
	ostream << "p edge " << _num_vertices << " " << _edges.size() << "\n";

	for (Edge const& edge : _edges) {
		ostream << "e " << edge.get_tail() + 1 << " " << edge.get_head() + 1 << "\n";
	}
}

void Dimac::read_dimac_file(std::string const& dimac_filename)
{
	std::ifstream dimac_file(dimac_filename);

	if (not dimac_file.is_open()) {
		std::cerr << "ERROR: cannot open file " << dimac_filename << "\n";
		throw;
	}

	std::string line;
	std::stringstream stringstream;

	std::string line_type;

	std::size_t num_vertices = std::numeric_limits<std::size_t>::max();
	std::size_t num_edges = std::numeric_limits<std::size_t>::max();

	while (std::getline(dimac_file, line)) {
		stringstream.clear();
		stringstream.str(line);

		stringstream >> line_type;

		assert(line_type != "e");

		if (line_type == "p") {
			std::string problem;

			stringstream >> problem;
			stringstream >> num_vertices;
			stringstream >> num_edges;

			break;
		}
	}

	assert(num_vertices < std::numeric_limits<std::size_t>::max());
	assert(num_edges < std::numeric_limits<std::size_t>::max());

	_num_vertices = num_vertices;

	_edges.reserve(num_edges);

	while (std::getline(dimac_file, line)) {
		stringstream.clear();
		stringstream.str(line);

		stringstream >> line_type;

		if (line_type == "e") {
			graph::Vertex::Index tail = graph::Vertex::invalid_index();
			graph::Vertex::Index head = graph::Vertex::invalid_index();

			stringstream >> tail;
			stringstream >> head;

			assert(tail != head);
			assert(tail > 0);
			assert(head > 0);
			assert(tail <= _num_vertices);
			assert(head <= _num_vertices);

			_edges.emplace_back(tail - 1, head - 1);
		}
	}

	assert(_edges.size() == num_edges);
}

} // namespace graph
