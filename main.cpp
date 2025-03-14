#include <fstream>
#include <iostream>
#include <set>
#include <cstdint>
#include <vector>

const size_t INF = SIZE_MAX;
const size_t SIMPLE_LENGTH = 1;
const std::string FILE_PATH = "../graph.txt";

void isPossibleParsing(std::ifstream& parser) {
    if (parser.eof()) {
        throw std::runtime_error("Incorrect input data\n");
    }
}

void
parseData(size_t &start_vertex, std::vector<size_t> &distances, std::set<std::pair<size_t, size_t>> &dijkstra_queue,
          std::vector<std::vector<size_t>> &graph_topology) {
    size_t vertexes_amount, edges_amount;
    std::ifstream parser;
    parser.open(FILE_PATH);
    if (!parser.is_open()) {
        throw std::runtime_error("Error during file opening\n");
    }
    isPossibleParsing(parser);
    parser >> vertexes_amount;
    isPossibleParsing(parser);
    parser >> edges_amount;

    distances.resize(vertexes_amount, INF);
    graph_topology.resize(vertexes_amount);
    for (size_t line = 0; line < edges_amount; ++line) {
        int first_vertex;
        isPossibleParsing(parser);
        parser >> first_vertex;
        int second_vertex;
        isPossibleParsing(parser);
        parser >> second_vertex;

        dijkstra_queue.insert({INF, first_vertex});
        dijkstra_queue.insert({INF, second_vertex});
        graph_topology[first_vertex].emplace_back(second_vertex);
        graph_topology[second_vertex].emplace_back(first_vertex);
    }
    isPossibleParsing(parser);
    parser >> start_vertex;
}

void applyDijkstra(const size_t start_vertex, std::vector<size_t> &distances,
                   std::set<std::pair<size_t, size_t>> &dijkstra_queue,
                   const std::vector<std::vector<size_t>> &graph_topology) {
    distances[start_vertex] = 0;
    dijkstra_queue.insert({0, start_vertex});
    dijkstra_queue.erase({INF, start_vertex});

    while (!dijkstra_queue.empty()) {
        size_t num_top = dijkstra_queue.begin()->second;
        dijkstra_queue.erase(dijkstra_queue.begin());
        for (size_t new_top_dist: graph_topology[num_top]) {
            size_t new_top = new_top_dist;
            size_t distance = SIMPLE_LENGTH;
            if (distances[num_top] + distance < distances[new_top]) {
                dijkstra_queue.erase({distances[new_top], new_top});
                distances[new_top] = distances[num_top] + distance;
                dijkstra_queue.insert({distances[new_top], new_top});
            }
        }
    }
}

void printAnswer(std::vector<size_t> &distances) {
    for (size_t distance: distances) {
        std::cout << distance << '\n';
    }
}

void solve() {
    size_t start_vertex;
    std::vector<size_t> distances;
    std::set<std::pair<size_t, size_t>> dijkstra_queue;
    std::vector<std::vector<size_t>> graph_topology;
    try {
        parseData(start_vertex, distances, dijkstra_queue, graph_topology);
        applyDijkstra(start_vertex, distances, dijkstra_queue, graph_topology);
        printAnswer(distances);
    } catch (std::exception& exception) {
        std::cerr << exception.what();
        exit(1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    solve();
    return 0;
}