// utils.hpp
#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP

#include "UndirectedGraph.hpp"
#include "matching/Matching.hpp"

namespace graph {

bool contains_edge(UndirectedGraph const& undirected_graph,
				   Vertex::Index const vertex_id_1,
				   Vertex::Index const vertex_id_2);

bool contains_edge(UndirectedGraph const& undirected_graph, Edge const& edge);

bool is_valid_matching(UndirectedGraph const& undirected_graph, Matching const& matching);

} // namespace graph

#endif
