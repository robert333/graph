// AlternatingTree.hpp
#ifndef GRAPH_ALTERNATINGTREE_HPP
#define GRAPH_ALTERNATINGTREE_HPP

#include "../Components.hpp"
#include "../Edge.hpp"

#include "Matching.hpp"

namespace graph {

class AlternatingTree {
public:
	class Node {
	public:
		using Level = std::size_t;
		using Vector = std::vector<Node>;

	public:
		Level level; /**< indicates on which level the node is in the current tree */

		Vertex::Index incoming_vertex_id; /**< the unique parent node */

		Vertex::Index odd_cycle_base_vertex_id; /**< if the node is contained in a shrunken odd cycle this will indicate the base of this cycle */

		Vertex::Index matching_neighbour; /**< the matching neighbour of the node in our tree (only the root has none) */

		Vertex::Index non_matching_base_vertex_id; /**< the non matching neighbour in a shrunken odd cycle */
		Edge non_matching_edge; /**< the non matching edge in a shrunken odd cycle */
	};

public:
	/**
	 * @brief constructor: initialises a alternating tree used in our matching algorithm
	 * @param num_nodes number of vertices in our undirected graph
	 */
	AlternatingTree(std::size_t const num_nodes);

	/**
	 * @brief resets the current alternating tree which contains only the root node
	 * @param root_id the new root node for the new alternating tree
	 */
	void reset(Vertex::Index const root_id);

	/**
	 * @brief adds a node to our current alternating tree
	 * @param vertex_id the vertex that will be added as a node to our tree
	 * @param incoming_vertex_id the unique incoming node in our tree
	 */
	void add_node(Vertex::Index const vertex_id, Vertex::Index const incoming_vertex_id);

	/**
	 * @brief checks whether the given vertex is the current root of our tree
	 */
	bool is_root(Vertex::Index const vertex_id) const;

	/**
	 * @brief checks whether the given vertex is contained in our current tree
	 */
	bool contains_node(Vertex::Index const vertex_id) const;

	/**
	 * @return the vertices that are contained in the current tree
	 */
	std::vector<Vertex::Index> get_contained_nodes() const;

	bool is_even_node(Vertex::Index const vertex_id) const;
	std::size_t get_level(Vertex::Index const vertex_id) const;
	Vertex::Index get_odd_cycle_base_vertex_id(Vertex::Index const vertex_id) const;

	Vertex::Index find_base_vertex_id(Vertex::Index const vertex_id);
	bool are_in_same_component(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2);

	Vertex::Index get_incoming_vertex_id(Vertex::Index const vertex_id) const;

	void set_matching_neighbour(Vertex::Index const vertex_id, Vertex::Index const matching_neighbour);
	Vertex::Index get_matching_neighbour(Vertex::Index const vertex_id) const;

	void set_incident_base_node(Vertex::Index const vertex_id, Vertex::Index const incident_base_vertex_id);
	void set_non_matching_edge(Vertex::Index const vertex_id, Edge const& non_matching_edge);
	Vertex::Index get_incident_base_node(Vertex::Index const vertex_id) const;
	Edge const& get_non_matching_edge(Vertex::Index const vertex_id) const;

	void shrink(Vertex::Index const base_vertex_id, std::vector<Vertex::Index> const& nodes_in_odd_cycle);

	// debug
//	void output_tree();
//	void output_node(Vertex::Index const vertex_id, std::string const& name);
//	void output_edge(Vertex::Index const tail_id, Vertex::Index const head_id, std::string const& name);

private:

private:
	std::size_t const _num_nodes; /**< number of nodes that are available for adding to the tree */

	Vertex::Index _root_node; /**< the current root of our tree */

	Node::Vector _nodes; /**< all available nodes regardless whether they are contained in our current tree or not */

	std::size_t _current_iteration; /**< the current iteration of our algorithm (increases each time we reset the tree) */

	std::vector<std::size_t> _contains_node; /**< indicates whether a node is contained in the current tree (_current_iteration == _contains_node[node_id]) */

	std::vector<Vertex::Index> _contained_nodes; /**< a set which contains only vertices that are contained in our current tree */

	Components _components; /**< a class which manages components of our tree (-> shrinking odd cycles) */
};

} // namespace graph

#endif
