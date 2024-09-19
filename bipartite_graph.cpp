#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <stack>

template <typename T>
struct Edge
{
	unsigned src;
	unsigned dst;
	T weight;
};

template <typename T>
class Graph
{
public:
	// N개의 정점으로 구성된 그래프
	Graph(unsigned N) : V(N) {}

	// 그래프의 정점 개수 반환
	auto vertices() const { return V; }

	// 전체 에지 리스트 반환
	auto& edges() const { return edge_list; }

	// 정점 v에서 나가는 모든 에지를 반환
	auto edges(unsigned v) const
	{
		std::vector<Edge<T>> edges_from_v;
		for (auto& e : edge_list)
		{
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}

		return edges_from_v;
	}

	void add_edge(Edge<T>&& e)
	{
		// 에지 양 끝 정점 ID가 유효한지 검사
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
			edge_list.emplace_back(e);
		else
			std::cerr << "에러: 유효 범위를 벗어난 정점!" << std::endl;
	}

	// 표준 출력 스트림 지원
	template <typename U>
	friend std::ostream& operator<< (std::ostream& os, const Graph<U>& G);

private:
	unsigned V;		// 정점 개수
	std::vector<Edge<T>> edge_list;
};

template <typename U>
std::ostream& operator<< (std::ostream& os, const Graph<U>& G)
{
	for (unsigned i = 1; i < G.vertices(); i++)
	{
		os << i << ":\t";

		auto edges = G.edges(i);
		for (auto& e : edges)
			os << "{" << e.dst << ": " << e.weight << "}, ";

		os << std::endl;
	}

	return os;
}

template <typename T>
auto create_bipartite_reference_graph()
{
	Graph<T> G(10);

	std::map<unsigned, std::vector<std::pair<unsigned, T>>> edge_map;
	edge_map[1] = { {2, 0} };
	edge_map[2] = { {1, 0}, {3, 0} , {8, 0} };
	edge_map[3] = { {2, 0}, {4, 0} };
	edge_map[4] = { {3, 0}, {6, 0} };
	edge_map[5] = { {7, 0}, {9, 0} };
	edge_map[6] = { {4, 0} };
	edge_map[7] = { {5, 0} };
	edge_map[8] = { {2, 0}, {9, 0} };
	edge_map[9] = { {5, 0}, {8, 0} };

	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{ i.first, j.first, j.second });

	return G;
}

template<typename T>
bool bipartite_check(Graph<T> input_graph) {
	std::stack<unsigned> stack;
	std::set<unsigned> visit_check;
	std::vector<unsigned> graph_color(input_graph.vertices(), 0);	// 없으면 : 0 검정색 : 1 빨간생 : 2
	unsigned last_color = 1;
	stack.push(1);
	while (!stack.empty()) {
		unsigned this_spot = stack.top();
		stack.pop();
		if (visit_check.find(this_spot) == visit_check.end()) {	//이전에 방문했는가?

			visit_check.insert(this_spot);
			graph_color[this_spot] = last_color;
			if (last_color == 1) {	//현재 정점을 검정색으로 칠해야 하는가?
				last_color = 2;
				std::cout << this_spot << " 정점 : 검정색" << std::endl;
			}
			else if (last_color == 2) {	//현재 정점을 빨간색으로 칠해야 하는가?
				last_color = 1;
				std::cout << this_spot << " 정점 : 빨간색" << std::endl;
			}
			for (auto edge : input_graph.edges(this_spot)) {
				if (visit_check.find(edge.dst) == visit_check.end()) {
					stack.push(edge.dst);
				}
			}
		} 
		if (graph_color[this_spot] != 0 && graph_color[this_spot] == last_color) {
			return false;
		}
	}

	return true;
}

int main()
{
	using T = unsigned;

	// 그래프 객체 생성
	auto BG = create_bipartite_reference_graph<T>();
	std::cout << "[입력 그래프]" << std::endl;
	std::cout << BG << std::endl;

	if (bipartite_check<T>(BG))
		std::cout << std::endl << "이분 그래프가 맞습니다." << std::endl;
	else
		std::cout << std::endl << "이분 그래프가 아닙니다." << std::endl;

}