cmake_minimum_required(VERSION 3.6)
project(Graph)

set(CMAKE_CXX_STANDARD 11)

set(WARNING_FLAGS "-Wall -Wextra -pedantic -Werror")

set(CMAKE_CXX_FLAGS "${WARNING_FLAGS}")

set(SOURCE_FILES
        source/typedefs.cpp
        source/UnionFind.cpp)

set(GRAPH_FILES
        source/graph/Vertex.cpp
        source/graph/Node.cpp
        source/graph/Edge.cpp
        source/graph/Graph.cpp
        source/graph/UndirectedGraph.cpp
        source/graph/GraphPrinter.cpp
        source/graph/GraphFactory.cpp
        source/graph/Components.cpp
        source/graph/utils.cpp
        source/graph/Dimac.cpp)

set(GRAPH_MATCHING_FILES
        source/graph/matching/Matching.cpp
        source/graph/matching/MatchingAlgorithms.cpp
        source/graph/matching/AlternatingTree.cpp)

set(DIJKSTRA_FILES
        source/graph/dijkstra/Dijkstra.cpp)

set(GRAPH_ALGORITHMS_FILES
        source/graph/algorithms/bfs.cpp
        source/graph/algorithms/dfs.cpp
        source/graph/algorithms/eul.cpp
        source/graph/algorithms/ikw.cpp
        source/graph/algorithms/isreachablefrom.cpp
        source/graph/algorithms/longestpath.cpp
        source/graph/algorithms/mbf.cpp
        source/graph/algorithms/scc.cpp
        source/graph/algorithms/topologicalsort.cpp
        source/graph/algorithms/zop.cpp)

set(MAIN_FILE
        source/main.cpp)

set(UNIT_TEST_FILES
        source/unit_tests/unit_tests.cpp
        source/unit_tests/test.cpp
        source/unit_tests/test_dijkstra.cpp
        source/unit_tests/test_perfect_matching.cpp
        source/unit_tests/test_maximum_matching.cpp
        source/unit_tests/test_matching_instances.cpp)

set(DEBUG_SOURCE_FILES
        source/debug.cpp
        source/Logger.cpp)

set(HELPER_SOURCE_FILES
        source/vector_helper.cpp)

add_executable(ProgrammingExercise
        source/UnionFind.cpp
        source/Logger.cpp
        source/graph/Dimac.cpp
        source/graph/Vertex.cpp
        source/graph/Edge.cpp
        source/graph/UndirectedGraph.cpp
        source/graph/Components.cpp
        source/graph/utils.cpp
        source/graph/matching/Matching.cpp
        source/graph/matching/MatchingAlgorithms.cpp
        source/graph/matching/AlternatingTree.cpp
        source/main.cpp)

add_executable(ProgrammingExercise_Unit_Tests
        source/UnionFind.cpp
        source/Logger.cpp
        source/graph/Dimac.cpp
        source/graph/Vertex.cpp
        source/graph/Edge.cpp
        source/graph/UndirectedGraph.cpp
        source/graph/Components.cpp
        source/graph/utils.cpp
        source/graph/matching/Matching.cpp
        source/graph/matching/MatchingAlgorithms.cpp
        source/graph/matching/AlternatingTree.cpp
        source/unit_tests/unit_tests.cpp
        source/unit_tests/test_perfect_matching.cpp
        source/unit_tests/test_maximum_matching.cpp
        source/unit_tests/test_matching_instances.cpp)

add_executable(Graph
        ${SOURCE_FILES}
        ${GRAPH_FILES}
        ${GRAPH_MATCHING_FILES}
        ${DIJKSTRA_FILES}
        ${GRAPH_ALGORITHMS_FILES}
        ${DEBUG_SOURCE_FILES}
        ${HELPER_SOURCE_FILES}
        ${MAIN_FILE})

add_executable(Graph_Unit_Tests
        ${SOURCE_FILES}
        ${GRAPH_FILES}
        ${GRAPH_MATCHING_FILES}
        ${DIJKSTRA_FILES}
        ${DEBUG_SOURCE_FILES}
        ${HELPER_SOURCE_FILES}
        ${UNIT_TEST_FILES})
