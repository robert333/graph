// utils.cpp
#include "utils.hpp"

#include <iostream>

#include "../vector_helper.hpp"

namespace graph {

bool contains_edge(UndirectedGraph const& undirected_graph,
				   Vertex::Index const vertex_id_1,
				   Vertex::Index const vertex_id_2)
{
	Vertex const& vertex_1 = undirected_graph.get_vertex(vertex_id_1);

	return helper::contains(vertex_1.get_neighbours(), vertex_id_2);
}

bool contains_edge(UndirectedGraph const& undirected_graph, Edge const& edge)
{
	return contains_edge(undirected_graph, edge.get_tail(), edge.get_head());
}

bool is_valid_matching(UndirectedGraph const& undirected_graph, Matching const& matching)
{
	std::size_t const num_vertices = undirected_graph.num_vertices();

	std::vector<bool> matched(num_vertices, false);
	std::vector<Vertex::Index> A;
	std::vector<Vertex::Index> B;

	A.reserve(num_vertices / 2);
	B.reserve(num_vertices / 2);

	for (Vertex::Index vertex_id = 0; vertex_id < num_vertices; ++vertex_id) {
		if (matched[vertex_id]) {
			continue;
		}

		if (matching.is_vertex_covered(vertex_id)) {
			Vertex::Index const matching_partner = matching.get_matching_partner(vertex_id);

			if (matched[vertex_id]) {
				std::cerr << "vertex " << vertex_id << " has more than one matching partner (one is "
						  << matching_partner << ")\n";
				return false;
			}

			if (matched[matching_partner]) {
				std::cerr << "vertex " << matching_partner << " has more than one matching partner (one is "
						  << vertex_id << ")\n";
				return false;
			}

			if (not contains_edge(undirected_graph, vertex_id, matching_partner)) {
				std::cerr << "matched nodes are not incident (" << vertex_id << " and " << matching_partner << ")\n";
				return false;
			}

			matched[vertex_id] = true;
			matched[matching_partner] = true;

			A.push_back(vertex_id);
			B.push_back(matching_partner);
		}
	}

	if (not helper::is_unique(A)) {
		std::cerr << "A is not unique!\n";
		return false;
	}

	if (not helper::is_unique(B)) {
		std::cerr << "B is not unique!\n";
		return false;
	}

	if (not helper::are_disjoint(A, B)) {
		std::cerr << "A and B are not disjoint!\n";
		return false;
	}

	return true;
}

} // namespace graph
