#include <cstdint>
#include <fstream>
#include <queue>
#include <iostream>
#include <set>
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
parseData(size_t &start_vertex, std::vector<size_t> &distances,
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

        graph_topology[first_vertex].emplace_back(second_vertex);
        graph_topology[second_vertex].emplace_back(first_vertex);
    }
    isPossibleParsing(parser);
    parser >> start_vertex;
}

void applyBFS(const size_t start_vertex, std::vector<size_t> &distances,
                   const std::vector<std::vector<size_t>> &graph_topology) {
    distances[start_vertex] = 0;
    std::queue<size_t> queue_vertexes;
    std::vector<bool> used(distances.size(), false);

    used[start_vertex] = true;
    queue_vertexes.push(start_vertex);
    while (!queue_vertexes.empty()) {
        size_t current_vertex = queue_vertexes.front();
        queue_vertexes.pop();
        for (size_t nearby_vertex : graph_topology[current_vertex]) {
            if (!used[nearby_vertex]) {
                used[nearby_vertex] = true;
                queue_vertexes.push(nearby_vertex);
                distances[nearby_vertex] = SIMPLE_LENGTH + distances[current_vertex];
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
        parseData(start_vertex, distances, graph_topology);
        applyBFS(start_vertex, distances, graph_topology);
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