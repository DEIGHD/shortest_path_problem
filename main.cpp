#include "graph\graph.hpp"
#include "matrix\matrix.hpp"
using namespace std;

int main()
{
	size_t vertices_count = 6;

	d8::graph<short> graph(vertices_count);

	d8::matrix<short> adjacency_matrix(vertices_count, vertices_count);
	adjacency_matrix =
	{
		{ 0, 1, 0, 0, 0, 0 },
		{ 1, 0, 1, 1, 1, 0 },
		{ 0, 1, 0, 1, 1, 0 },
		{ 0, 1, 1, 0, 1, 0 },
		{ 0, 1, 1, 1, 0, 1 },
		{ 0, 0, 0, 0, 1, 0 }
	};
	graph.from_adjacency_matrix(adjacency_matrix);

	auto path = graph.get_short_path(0, 5, d8::pfa::bfs);

	return 0;
}