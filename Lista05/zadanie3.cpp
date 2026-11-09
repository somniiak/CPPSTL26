#include <algorithm>
#include <print>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

bool is_letters (const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(),
    [](unsigned char c) { return std::isalpha(c); });
}

class DynamicGraph
{
    // [Wierzchołek] -> ([Sąsiad] -> Waga krawędzi)
    std::unordered_map<std::string, std::unordered_map<std::string, double>> neighbors;

    bool contains_vertex(const std::string& str) {
        return neighbors.find(str) != neighbors.end();
    }

    void require_vertices(const std::string& a, const std::string& b) {
        if (!contains_vertex(a) || !contains_vertex(b))
            throw std::invalid_argument("Operacja na nieistniejącym wierzchołku!");
    }

    bool contains_edge(const std::string& a, const std::string& b) {
        require_vertices(a, b);

        auto edgeA = neighbors[a].find(b);
        auto edgeB = neighbors[b].find(a);

        return (edgeA != neighbors[a].end() && edgeB != neighbors[b].end());
    }

    public:

    DynamicGraph() : neighbors() {}

    void add_vertex(const std::string& str) {
        if (!is_letters(str))
            throw std::invalid_argument("Nazwa wierzchołka musi być niepustym napisem z liter!");

        if (contains_vertex(str))
            throw std::invalid_argument("Wierzchołek " + str + " już istnieje!");

        neighbors[str];
    }

    void remove_vertex(const std::string& str) {
        auto it = neighbors.find(str);

        if (it == neighbors.end())
            throw std::invalid_argument("Nie można usunąć nieistniejącego wierzchołka!");

        for (const auto& [neighbor, weight] : it->second)
            if (neighbor != str)
                neighbors[neighbor].erase(str);

        neighbors.erase(it);
    }

    void add_edge(const std::string& a, const std::string& b, double weight) {
        require_vertices(a, b);

        if (contains_edge(a, b))
            throw std::logic_error("Krawędź już istnieje!");

        neighbors[a][b] = weight;
        neighbors[b][a] = weight;
    }

    void update_edge(const std::string& a, const std::string& b, double weight) {
        require_vertices(a, b);

        if (!contains_edge(a, b))
            throw std::logic_error("Nie można zaktualizować nieistniejącej krawędzi!");

        neighbors[a][b] = weight;
        neighbors[b][a] = weight;
    }

    void delete_edge(const std::string& a, const std::string& b) {
        require_vertices(a, b);

        if (!contains_edge(a, b))
            throw std::logic_error("Nie można usunąć nieistniejącej krawędzi!");

        neighbors[a].erase(b);
        neighbors[b].erase(a);
    }

    std::vector<std::tuple<std::string, std::string, double>> getEdgeList() {
        std::vector<std::tuple<std::string, std::string, double>> edges;

        for (const auto& [from, adjacent] : neighbors)
            for (const auto& [to, weight] : adjacent)
                if (from <= to)
                    edges.emplace_back(from, to, weight);

        return edges;
    }

    // https://www.algotree.org/algorithms/minimum_spanning_tree/prims_c++/

    DynamicGraph prim(const std::string& start) {
        using Edge = std::tuple<std::string, std::string, double>;

        auto heavier = [](const Edge& x, const Edge& y) {
            return std::get<2>(x) > std::get<2>(y);
        };

        // https://stackoverflow.com/a/48587737
        std::priority_queue<Edge, std::vector<Edge>, decltype(heavier)> pq(heavier);

        std::unordered_set<std::string> visited;
        DynamicGraph tree;

        visited.insert(start);
        tree.add_vertex(start);

        for (const auto& [to, weight] : neighbors.at(start))
            pq.emplace(start, to, weight);

        while (!pq.empty())
        {
            auto [from, to, w] = pq.top();
            pq.pop();

            if (visited.find(to) != visited.end())
                continue;

            visited.insert(to);
            tree.add_vertex(to);
            tree.add_edge(from, to, w);

            for (const auto& [n, nw] : neighbors.at(to))
                if (visited.find(n) == visited.end())
                    pq.emplace(to, n, nw);
        }

        return tree;
    }
};

int main()
{
    DynamicGraph graph;

    graph.add_vertex("A"); graph.add_vertex("B"); graph.add_vertex("C");
    graph.add_vertex("D"); graph.add_vertex("E"); graph.add_vertex("F");
    graph.add_vertex("G"); graph.add_vertex("H"); graph.add_vertex("I");

    graph.add_edge("A", "B", 3.5); graph.add_edge("B", "H", 2.7);
    graph.add_edge("H", "D", 9.8); graph.add_edge("H", "F", 6.7);
    graph.add_edge("D", "A", 6.9); graph.add_edge("A", "E", 4.2);
    graph.add_edge("E", "I", 1.5); graph.add_edge("I", "H", 1.9);
    graph.add_edge("H", "C", 3.5); graph.add_edge("C", "F", 3.2);

    double sum = 0;

    for (const auto& [from, to, weight] : graph.prim("A").getEdgeList()) {
        std::println("({}-{}: {})", from, to, weight); sum += weight;
    }

    std::println("Suma wag: {}", sum);

    return 0;
}
