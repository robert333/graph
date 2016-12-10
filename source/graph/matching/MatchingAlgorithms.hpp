// MatchingAlgorithms.hpp
#ifndef GRAPH_MATCHING_ALGORITHMS_HPP
#define GRAPH_MATCHING_ALGORITHMS_HPP

#include <deque>

#include "../../Logger.hpp"

#include "../UndirectedGraph.hpp"

#include "Matching.hpp"
#include "AlternatingTree.hpp"

namespace graph {

class MatchingAlgorithms
{
public:

public:
	/**
	 * @brief constructor: initialises the implemented matching algorithms
	 * @param undirected_graph the graph for which we have to find a matching
	 * @param initial_matching a initial matching in the given graph which should be used
	 * and in which we save the final matching for each algorithm
	 */
	MatchingAlgorithms(UndirectedGraph const& undirected_graph, Matching& initial_matching);

	/**
	 * @brief computes a maximal matching in the given graph saves it in _matching
	 * this routine can be used to extend the given initial matching (saved in _matching)
	 * such that the other algorithms will starting with a maximal matching
	 */
	void compute_greedy_matching();

	/**
	 * @brief computes a perfect matching if one exists otherwise the current alternating tree is frustrated
	 * regardless whether we found a perfect matching or not the last matching is saved in _matching
	 */
	void compute_perfect_matching();

	/**
	 * @brief computes a maximum matching
	 * the matching will be saved in _matching
	 */
	void compute_maximum_matching();

private:
	/**
	 * @brief checks whether a vertex is contained in a frustrated tree and not available anymore
	 */
	bool is_vertex_available(Vertex::Index const vertex_id) const;

	/**
	 * @brief finds next exposed vertex
	 * needed for determining next root node of the next alternating tree
	 */
	Vertex::Index get_next_exposed_node();

	/**
	 * @brief perfect matching algorithm
	 * @return false if and only if we computed a frustrated tree
	 */
	bool compute_matching();
	bool process_vertex(Vertex::Index const vertex_id);
	bool process_edge(Vertex::Index const vertex_id, Vertex::Index const neighbour_id);

	/**
	 * @brief shrinks a detected odd cycle within our alternating tree
	 * the odd cycle is induced by the incident nodes vertex_id_1 and vertex_id_2 of even components
	 */
	void shrink_odd_cycle(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2);

	/**
	 * @brief extend the alternating tree along even_vertex_id -- matched_neighbour_id == ..
	 */
	void extend_alternating_tree(Vertex::Index const even_vertex_id, Vertex::Index const matched_neighbour_id);

	/**
	 * @brief Augments current matching from exposed_vertex_id to the current root of the alternating tree
	 */
	void augment_matching(Vertex::Index const exposed_vertex_id, Vertex::Index const incoming_vertex_id);

	/**
	 * @brief Augments a odd cycle from entering_vertex_id to the root of the odd cycle
	 * @param entering_vertex_id The node of the odd cycle which is already matched
	 * @return Returns the base of the odd cycle
	 */
	Vertex::Index augment_odd_cycle(Vertex::Index const entering_vertex_id);

private:
	/**
	 * @brief debug routine
	 */
	void is_alternating_tree_valid();

private:
	UndirectedGraph const& _undirected_graph; /**< original graph for which we compute a matching */

	Matching& _matching; /**< current matching in each step of the algorithm */

	std::vector<bool> _is_vertex_available; /**< indicates whether a vertex is removed or still available */
	std::size_t _num_available_vertices;

	AlternatingTree _alternating_tree; /**< current alternating tree in each step of the algorithm */

	Vertex::Index _last_exposed_vertex; /**< last vertex that was exposed, required for determining next root node */
	std::deque<Vertex::Index> _even_vertices; /**< list off all vertices whose incident edges still have to be considered */

	Logger _logger;
};

} // namespace graph

#endif
