// MatchingAlgorithms.cpp
#include "MatchingAlgorithms.hpp"

#include "../../debug.hpp"

#include "../utils.hpp"

namespace graph {

MatchingAlgorithms::MatchingAlgorithms(UndirectedGraph const& undirected_graph, Matching& initial_matching) :
	_undirected_graph(undirected_graph),
	_matching(initial_matching),
	_alternating_tree(undirected_graph.num_vertices()),
	_last_exposed_vertex(Vertex::invalid_index()),
	_logger(std::cout)
{
	
}

void MatchingAlgorithms::compute_greedy_matching()
{
	_logger << "== Compute Greedy Matching ==\n\n";

	for (Vertex::Index vertex_id = 0; vertex_id < _undirected_graph.num_vertices(); ++vertex_id) {
		if (_matching.is_vertex_covered(vertex_id)) {
			continue;
		}

		Vertex const& vertex =_undirected_graph.get_vertex(vertex_id);

		for (Vertex::Index const neighbour_id : vertex.get_neighbours()) {
			if (not _matching.is_vertex_covered(neighbour_id)) {
				_matching.match(vertex_id, neighbour_id);
				break;
			}
		}
	}

	assert(is_valid_matching(_undirected_graph, _matching));

	_logger << "=============================\n\n";
}

void MatchingAlgorithms::compute_perfect_matching()
{
	_logger << "== Compute Perfect Matching ==\n\n";

	_is_vertex_available.assign(_undirected_graph.num_vertices(), true);
	_num_available_vertices = _undirected_graph.num_vertices();

	bool const perfect = compute_matching();

	assert(is_valid_matching(_undirected_graph, _matching));

	if (perfect) {
		assert(_matching.is_perfect());
		_logger << "\nfound perfect matching\n";
	} else {
		_logger << "\nthere exists no perfect matching\n";
	}

	_logger << "==============================\n\n";
}

void MatchingAlgorithms::compute_maximum_matching()
{
//	_logger << "== Compute Maximum Matching ==\n\n";

	_is_vertex_available.assign(_undirected_graph.num_vertices(), true);
	_num_available_vertices = _undirected_graph.num_vertices();

//	std::size_t num_frustrated_alternating_trees = 0;
//	double progress = (2. * _matching.cardinality() + num_frustrated_alternating_trees) / (_undirected_graph.num_vertices() / 100.);
//	std::cout << "we have already processed " << progress << "%\n";

	// while there are vertices left we may not computed a maximum matching
	while (_num_available_vertices > 0) {
		// try to compute a perfect matching in our current graph
		bool const perfect = compute_matching();

		if (perfect) {
			break;
		} else {
//			++num_frustrated_alternating_trees;
		}

//		double new_progress = (2. * _matching.cardinality() + num_frustrated_alternating_trees) / (_undirected_graph.num_vertices() / 100.);
//
//		if (progress + 1 <= new_progress) {
//			progress = new_progress;
//			std::cout << "current progress " << progress << "%\n";
//		}
//
//		_logger << "current number of frustrated alternating trees = " << num_frustrated_alternating_trees << "\n\n";

		// remove the computed frustrated tree from our current graph
		for (Vertex::Index const vertex_id : _alternating_tree.get_contained_nodes()) {
			assert(_alternating_tree.contains_node(vertex_id));
			assert(_num_available_vertices > 0);
			_is_vertex_available[vertex_id] = false;
			--_num_available_vertices;
		}
	}

	assert(is_valid_matching(_undirected_graph, _matching));

//	std::cout << "maximum matching consists of " << _matching.cardinality() << " edges and "
//			<< num_frustrated_alternating_trees << " exposed nodes\n\n";
//
//	_logger << "==============================\n\n";
}

bool MatchingAlgorithms::is_vertex_available(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _undirected_graph.num_vertices()));
	assert(_is_vertex_available.size() == _undirected_graph.num_vertices());
	return _is_vertex_available[vertex_id];
}

Vertex::Index MatchingAlgorithms::get_next_exposed_node()
{
	assert(_last_exposed_vertex == Vertex::invalid_index()
		   or _matching.is_vertex_covered(_last_exposed_vertex)
		   or _alternating_tree.is_root(_last_exposed_vertex));

	Vertex::Index const first_next_id = (_last_exposed_vertex == Vertex::invalid_index()) ? 0 : _last_exposed_vertex + 1;

	for (Vertex::Index vertex_id = first_next_id; vertex_id < _undirected_graph.num_vertices(); ++vertex_id) {
		if (not _matching.is_vertex_covered(vertex_id)) {
			_last_exposed_vertex = vertex_id;
			return vertex_id;
		}
	}

	return Vertex::invalid_index();
}

bool MatchingAlgorithms::compute_matching()
{
	assert(_is_vertex_available.size() == _undirected_graph.num_vertices());

#ifndef NDEBUG
	std::size_t const initial_matching_cardinality = _matching.cardinality();
#endif
	std::size_t num_alternating_trees = 1;

	Vertex::Index const start_root = get_next_exposed_node();

	if (start_root == Vertex::invalid_index()) {
		return true;
	}

	assert(is_vertex_available(start_root));
	assert(_even_vertices.empty());

	// initialise alternating tree with the computed exposed vertex
	_even_vertices.push_back(start_root);
	_alternating_tree.reset(start_root);

	while (not _even_vertices.empty()) {
//		assert(helper::is_unique(_even_nodes));

		Vertex::Index const even_vertex_id = _even_vertices.front();
		_even_vertices.pop_front();

		assert(Vertex::is_index_valid(even_vertex_id, _undirected_graph.num_vertices()));
		assert(is_vertex_available(even_vertex_id));

		// iff process_vertex returns true we have augmented our matching
		// and we need to check if we are perfect or another iteration with a new root is needed
		if (process_vertex(even_vertex_id)) {
			assert(is_valid_matching(_undirected_graph, _matching));
			assert(_matching.cardinality() == initial_matching_cardinality + num_alternating_trees);

			if (_matching.is_perfect()) {
				return true;
			} else {
				Vertex::Index const new_root = get_next_exposed_node();

				if (new_root == Vertex::invalid_index()) {
					return true;
				}

				assert(is_vertex_available(new_root));
				_alternating_tree.reset(new_root);
				_even_vertices = {new_root};
				++num_alternating_trees;
			}
		}
	}

	assert(is_valid_matching(_undirected_graph, _matching));
	assert(not _matching.is_perfect());

	return false;
}

bool MatchingAlgorithms::process_vertex(Vertex::Index const vertex_id)
{
	assert(_alternating_tree.contains_node(vertex_id));
	assert(_alternating_tree.is_even_node(_alternating_tree.find_base_vertex_id(vertex_id)));
	assert(is_vertex_available(vertex_id));

	Vertex const& vertex = _undirected_graph.get_vertex(vertex_id);

	for (Vertex::Index const neighbour_id : vertex.get_neighbours()) {
		if (not is_vertex_available(neighbour_id)) {
			continue;
		}

		// iff process_edge returns true we have augmented our matching
		if (process_edge(vertex_id, neighbour_id)) {
			return true;
		}
	}

	return false;
}

bool MatchingAlgorithms::process_edge(Vertex::Index const vertex_id, Vertex::Index const neighbour_id)
{
	// core algorithm
	// here we check which case need to be considered for the given edge
	if (_alternating_tree.contains_node(neighbour_id)) {
		Vertex::Index const tail_component = _alternating_tree.find_base_vertex_id(vertex_id);
		Vertex::Index const head_component = _alternating_tree.find_base_vertex_id(neighbour_id);

		assert(_alternating_tree.is_even_node(tail_component));

		// edge is within a shrunken odd cycle
		if (tail_component == head_component) {
			return false;
		}

		if (_alternating_tree.is_even_node(head_component)) {
			shrink_odd_cycle(vertex_id, neighbour_id);
//			is_alternating_tree_valid();
		}
	} else {
		if (_matching.is_vertex_covered(neighbour_id)) {
			extend_alternating_tree(vertex_id, neighbour_id);
		} else {
			augment_matching(neighbour_id, vertex_id);
			return true;
		}
	}

	return false;
}

void MatchingAlgorithms::shrink_odd_cycle(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2)
{
	assert(Vertex::is_index_valid(vertex_id_1, _undirected_graph.num_vertices()));
	assert(Vertex::is_index_valid(vertex_id_2, _undirected_graph.num_vertices()));
	assert(_alternating_tree.contains_node(vertex_id_1));
	assert(_alternating_tree.contains_node(vertex_id_2));
	assert(vertex_id_1 != vertex_id_2);
	assert(contains_edge(_undirected_graph, vertex_id_1, vertex_id_2));
	assert(contains_edge(_undirected_graph, vertex_id_2, vertex_id_1));

	Vertex::Index current_component_1 = _alternating_tree.find_base_vertex_id(vertex_id_1);
	Vertex::Index current_component_2 = _alternating_tree.find_base_vertex_id(vertex_id_2);

	assert(_alternating_tree.is_even_node(current_component_1));
	assert(_alternating_tree.is_even_node(current_component_2));

	bool neighbours_1_matched = true;
	bool neighbours_2_matched = true;

	_alternating_tree.set_incident_base_node(current_component_1, current_component_2);
	_alternating_tree.set_incident_base_node(current_component_2, current_component_1);
	_alternating_tree.set_non_matching_edge(current_component_1, Edge(vertex_id_1, vertex_id_2));
	_alternating_tree.set_non_matching_edge(current_component_2, Edge(vertex_id_2, vertex_id_1));

	std::vector<Vertex::Index> nodes_in_odd_cycle;

	// since we know for each component a level in our alternating tree (not necessary the minimal one)
	// we can compute in O(|E(C)|)-time the odd cycle C
	// we search simultaneously for the two paths to the branching vertex
	// if we reached the branching vertex / base vertex of our odd cycle we are done
	while (current_component_1 != current_component_2) {
		if (_alternating_tree.get_level(current_component_1) >= _alternating_tree.get_level(current_component_2)) {
			assert(Vertex::is_index_valid(current_component_1, _undirected_graph.num_vertices()));
			assert(not _alternating_tree.is_root(current_component_1));

			nodes_in_odd_cycle.push_back(current_component_1);

			if (not _alternating_tree.is_even_node(current_component_1)) {
				_even_vertices.push_back(current_component_1);
			}

			Vertex::Index const current_neighbour = _alternating_tree.get_incoming_vertex_id(current_component_1);
			Vertex::Index const current_neighbour_component = _alternating_tree.find_base_vertex_id(current_neighbour);

			assert(contains_edge(_undirected_graph, current_component_1, current_neighbour));
			assert(contains_edge(_undirected_graph, current_neighbour, current_component_1));

			if (not neighbours_1_matched) {
				_alternating_tree.set_incident_base_node(current_component_1, current_neighbour_component);
				_alternating_tree.set_incident_base_node(current_neighbour_component, current_component_1);
				_alternating_tree.set_non_matching_edge(current_component_1, Edge(current_component_1, current_neighbour));
				_alternating_tree.set_non_matching_edge(current_neighbour_component, Edge(current_neighbour, current_component_1));
			}

			current_component_1 = current_neighbour_component;
			neighbours_1_matched = not neighbours_1_matched;
		}

		// if we reached the branching vertex / base vertex of our odd cycle we are done
		if (current_component_1 == current_component_2) {
			break;
		}

		if (_alternating_tree.get_level(current_component_2) >= _alternating_tree.get_level(current_component_1)) {
			assert(Vertex::is_index_valid(current_component_2, _undirected_graph.num_vertices()));
			assert(not _alternating_tree.is_root(current_component_2));

			nodes_in_odd_cycle.push_back(current_component_2);

			if (not _alternating_tree.is_even_node(current_component_2)) {
				_even_vertices.push_back(current_component_2);
			}

			Vertex::Index const current_neighbour = _alternating_tree.get_incoming_vertex_id(current_component_2);
			Vertex::Index const current_neighbour_component = _alternating_tree.find_base_vertex_id(current_neighbour);

			assert(contains_edge(_undirected_graph, current_component_2, current_neighbour));
			assert(contains_edge(_undirected_graph, current_neighbour, current_component_2));

			if (not neighbours_2_matched) {
				_alternating_tree.set_incident_base_node(current_component_2, current_neighbour_component);
				_alternating_tree.set_incident_base_node(current_neighbour_component, current_component_2);
				_alternating_tree.set_non_matching_edge(current_component_2, Edge(current_component_2, current_neighbour));
				_alternating_tree.set_non_matching_edge(current_neighbour_component, Edge(current_neighbour, current_component_2));
			}

			current_component_2 = current_neighbour_component;
			neighbours_2_matched = not neighbours_2_matched;
		}

		assert(Vertex::is_index_valid(current_component_1, _undirected_graph.num_vertices()));
		assert(Vertex::is_index_valid(current_component_2, _undirected_graph.num_vertices()));
	}

	assert(current_component_1 == current_component_2);
	assert(_alternating_tree.is_even_node(current_component_1));
	assert(_alternating_tree.get_level(current_component_1) <= _alternating_tree.get_level(vertex_id_1));
	assert(_alternating_tree.get_level(current_component_1) <= _alternating_tree.get_level(vertex_id_2));

	Vertex::Index const base_vertex_id = current_component_1;

	_alternating_tree.shrink(base_vertex_id, nodes_in_odd_cycle);
}

void MatchingAlgorithms::extend_alternating_tree(Vertex::Index const even_vertex_id, Vertex::Index const matched_neighbour_id)
{
	Vertex::Index const matching_partner = _matching.get_matching_partner(matched_neighbour_id);

	assert(is_vertex_available(matched_neighbour_id));
	assert(is_vertex_available(matching_partner));

	_alternating_tree.add_node(matched_neighbour_id, even_vertex_id);
	_alternating_tree.add_node(matching_partner, matched_neighbour_id);

	_alternating_tree.set_matching_neighbour(matched_neighbour_id, matching_partner);
	_alternating_tree.set_matching_neighbour(matching_partner, matched_neighbour_id);

	_even_vertices.push_back(matching_partner);
}

void MatchingAlgorithms::augment_matching(Vertex::Index const exposed_vertex_id, Vertex::Index const incoming_vertex_id)
{
	_matching.match(exposed_vertex_id, incoming_vertex_id);

	Vertex::Index current_vertex_id = incoming_vertex_id;

	while (true) {
		assert(Vertex::is_index_valid(current_vertex_id, _undirected_graph.num_vertices()));
		assert(Vertex::is_index_valid(_alternating_tree.find_base_vertex_id(current_vertex_id), _undirected_graph.num_vertices()));
		assert(_alternating_tree.is_even_node(_alternating_tree.find_base_vertex_id(current_vertex_id)));

		// whenever the current vertex is contained in shrunken odd cycle we first augment this one
		Vertex::Index odd_cycle_id = _alternating_tree.get_odd_cycle_base_vertex_id(current_vertex_id);

		while (odd_cycle_id != current_vertex_id) {
			current_vertex_id = augment_odd_cycle(current_vertex_id);
			odd_cycle_id = _alternating_tree.get_odd_cycle_base_vertex_id(current_vertex_id);
		}

		assert(current_vertex_id == odd_cycle_id);
		assert(current_vertex_id == _alternating_tree.find_base_vertex_id(current_vertex_id));

		if (_alternating_tree.is_root(current_vertex_id)) {
			return;
		}

		Vertex::Index const incoming_odd_vertex_id = _alternating_tree.get_incoming_vertex_id(current_vertex_id);
		Vertex::Index const incoming_even_vertex_id = _alternating_tree.get_incoming_vertex_id(incoming_odd_vertex_id);

		assert(_alternating_tree.get_level(current_vertex_id) == _alternating_tree.get_level(incoming_odd_vertex_id) + 1);
		assert(not _alternating_tree.is_even_node(incoming_odd_vertex_id));
		assert(_alternating_tree.find_base_vertex_id(incoming_odd_vertex_id) == incoming_odd_vertex_id);
		assert(_alternating_tree.get_odd_cycle_base_vertex_id(incoming_odd_vertex_id) == incoming_odd_vertex_id);

		_matching.divorce(current_vertex_id, incoming_odd_vertex_id);
		_matching.match(incoming_odd_vertex_id, incoming_even_vertex_id);

		current_vertex_id = incoming_even_vertex_id;
	}
}

Vertex::Index MatchingAlgorithms::augment_odd_cycle(Vertex::Index const entering_vertex_id)
{
	Vertex::Index const odd_cycle_id = _alternating_tree.get_odd_cycle_base_vertex_id(entering_vertex_id);
	assert(odd_cycle_id != entering_vertex_id);

	bool matched = true;
	Vertex::Index current_base_vertex_id = entering_vertex_id;

	while (odd_cycle_id != current_base_vertex_id) {
		Vertex::Index const incident_base_vertex_id = matched ?
													  _alternating_tree.get_matching_neighbour(current_base_vertex_id) :
													  _alternating_tree.get_incident_base_node(current_base_vertex_id);

		if (matched) {
//			assert(incident_base_vertex_id == _matching.get_matching_partner(current_base_vertex_id));
			_matching.divorce(current_base_vertex_id, incident_base_vertex_id);
		} else {
			Edge const& incident_edge = _alternating_tree.get_non_matching_edge(current_base_vertex_id);
			assert(contains_edge(_undirected_graph, incident_edge));

			Vertex::Index tmp_vertex_id = incident_edge.get_tail();

			while (tmp_vertex_id != current_base_vertex_id) {
				tmp_vertex_id = augment_odd_cycle(tmp_vertex_id);
			}

			tmp_vertex_id = incident_edge.get_head();

			while (tmp_vertex_id != incident_base_vertex_id) {
				tmp_vertex_id = augment_odd_cycle(tmp_vertex_id);
			}

			_matching.match(incident_edge);
		}

		current_base_vertex_id = incident_base_vertex_id;
		matched = not matched;
	}

	return current_base_vertex_id;
}

void MatchingAlgorithms::is_alternating_tree_valid()
{
#ifndef NDEBUG
	for (Vertex::Index vertex_id = 0; vertex_id < _undirected_graph.num_vertices(); ++vertex_id) {
		if (not _alternating_tree.contains_node(vertex_id)) {
			continue;
		}

		if (not _alternating_tree.is_root(vertex_id)) {
			Vertex::Index const incoming_vertex_id = _alternating_tree.get_incoming_vertex_id(vertex_id);

			assert(contains_edge(_undirected_graph, vertex_id, incoming_vertex_id));
			assert(contains_edge(_undirected_graph, incoming_vertex_id, vertex_id));

			if (_alternating_tree.find_base_vertex_id(vertex_id) != _alternating_tree.find_base_vertex_id(incoming_vertex_id)) {
				assert(_alternating_tree.get_level(_alternating_tree.find_base_vertex_id(vertex_id)) > _alternating_tree.get_level(_alternating_tree.find_base_vertex_id(incoming_vertex_id)));
			}
		}

		if (_alternating_tree.get_odd_cycle_base_vertex_id(vertex_id) == vertex_id) {
			continue;
		}

		Edge const& incident_non_matching_edge = _alternating_tree.get_non_matching_edge(vertex_id);
		assert(contains_edge(_undirected_graph, incident_non_matching_edge.get_tail(), incident_non_matching_edge.get_head()));
		assert(contains_edge(_undirected_graph, incident_non_matching_edge.get_head(), incident_non_matching_edge.get_tail()));
	}
#endif
}

} // namespace graph
