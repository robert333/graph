// typedefs.hpp
#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <vector>
#include <deque>
#include <map>
#include <memory>
#include <limits>

#include "debug.hpp"
#include "vector_helper.hpp"

using NodeId = std::size_t;
using EdgeId = std::size_t;
using Weight = double;

NodeId invalid_node_id();
EdgeId invalid_edge_id();

bool is_node_id_valid(NodeId const node_id, std::size_t const num_nodes);
bool is_edge_id_valid(EdgeId const edge_id, std::size_t const num_edges);

#endif
