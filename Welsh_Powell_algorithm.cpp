#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>


// 그래프 컬러링에 사용할 색상 번호
std::unordered_map<unsigned, std::string> color_map = {
	{1, "Red"},
	{2, "Blue"},
	{3, "Green"},
	{4, "Yellow"},
	{5, "Black"},
	{6, "White"}
};

template <typename T>
struct Edge {
	unsigned src;
	unsigned dst;
	T weight;
	inline bool operator< (const Edge<T>& e) const {
		return this->weight < e.weight;
	}
	inline bool operator> (const Edge<T>& e) const {
		return this->weight > e.weight;
	}
};

template <typename T>
class Graph {
private:
	unsigned V;
	std::vector<Edge<T>> edge_list;
public:
	Graph(unsigned N) : V(N) {}
	auto vertices() const { return V; }	// 그래프의 정점개수 반환
	auto& edges() const { return edge_list; }	//전체 에지 리스트 반환
	// 정점 v에서 나가는 모든 에지를 반환
	auto edges(unsigned v) const {
		std::vector<Edge<T>> edges_from_v;
		for (auto& e : edge_list) {
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}
		return edges_from_v;
	}
	void add_edge(Edge<T>&& e) {
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
			edge_list.emplace_back(e);
		else
			std::cerr << "에러 : 유효 범위를 벗어난 정점!" << std::endl;
	}
	template <typename U>
	friend std::ostream& operator<< (std::ostream& os, const Graph<U>& G);
	
};

template <typename U>
std::ostream& operator<<(std::ostream& os, const Graph<U>& G) {
	for (unsigned i = 1; i < G.vertices(); i++) {
		os << i << ":\t";
		auto edges = G.edges(i);
		for (auto& e : edges) {
			os << "{" << e.dst << ": " << e.weight << "}, ";
		}
		os << std::endl;
	}
	return os;
}

template <typename T>
void print_colors(std::vector<T>& colors)
{
	for (auto i = 1; i < colors.size(); i++)
	{
		std::cout << i << ": " << color_map[colors[i]] << std::endl;
	}
}

template<typename T>
auto welsh_powell_coloring(const Graph<T>& G) {
	std::vector<std::pair<unsigned, size_t>> vertexes;
	for (unsigned i = 1; i < G.vertices(); i++) {
		vertexes.push_back(std::make_pair(i,G.edges(i).size()));
	}
	std::sort(vertexes.begin(), vertexes.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
		});
	std::cout << "[색상 지정 순서(괄호는 차수)]" << std::endl;
	for (auto const it : vertexes) {
		std::cout << it.first << " (" << it.second << ")" << std::endl;
	}

	std::vector<int> colors(G.vertices(), 0); //노드에 들어간 색상
	std::vector<bool> used_color(color_map.size() + 1, false); // 사용할 수 있는 색상들
	for (auto const vertex : vertexes) {
		std::vector<int> connected_vertex;	//연결된 노드들
		std::fill(used_color.begin(), used_color.end(), false);
		for (int i = 0; i < vertex.second; i++) {	//현재 노드에 연결된 노드 구하기
			std::vector<Edge<T>> vertex_edges = G.edges(vertex.first);
			for (auto const this_edge : vertex_edges) {
				connected_vertex.push_back(this_edge.dst);
			}
		}
		for (auto const vertex : connected_vertex) {	//연결된 노드에 사용된 색상을 구한다
			if (colors[vertex] != 0) {
				used_color[colors[vertex]] = true;
			}
		}
		for (size_t i = 1; i < used_color.size(); ++i) {
			if (!used_color[i]) {
				colors[vertex.first] = i;
				break;
			}
		}

	}
	return colors;
}
int main()
{
	using T = unsigned;

	// 그래프 객체 생성
	Graph<T> G(9);
	std::map<unsigned, std::vector<std::pair<unsigned, T>>> edge_map;
	edge_map[1] = { {2, 0}, {5, 0} };
	edge_map[2] = { {1, 0}, {5, 0}, {4, 0} };
	edge_map[3] = { {4, 0}, {7, 0} };
	edge_map[4] = { {2, 0}, {3, 0}, {5, 0}, {6, 0}, {8, 0} };
	edge_map[5] = { {1, 0}, {2, 0}, {4, 0}, {8, 0} };
	edge_map[6] = { {4, 0}, {7, 0}, {8, 0} };
	edge_map[7] = { {3, 0}, {6, 0} };
	edge_map[8] = { {4, 0}, {5, 0}, {6, 0} };

	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{ i.first, j.first, j.second });

	std::cout << "[입력 그래프]" << std::endl;
	std::cout << G << std::endl;

	auto colors = welsh_powell_coloring<T>(G);
	std::cout << std::endl << "[그래프 컬러링]" << std::endl;
	print_colors(colors);
}