#pragma once
#include "graph.hpp"
#include <vector>
#include <queue>


template<typename TYPE>
d8::graph_path<TYPE> d8::graph<TYPE>::breadth_firts_search(size_t start_vertex, size_t goal_vertex) const
{
	size_t vertices_count = m_weight_matrix.get_row_count();
	std::vector<size_t> prev(vertices_count, SIZE_MAX);

	std::queue<size_t> queue;
	d8::graph_path<TYPE> path;

	queue.push(start_vertex);
	prev[start_vertex] = start_vertex;

	size_t current_vertex;

	while (!queue.empty())
	{
		current_vertex = queue.front();
		queue.pop();
		for (size_t i = 0; i < vertices_count; i++)
		{
			if (prev[i] == SIZE_MAX && m_weight_matrix(current_vertex, i) != 0 && m_weight_matrix(current_vertex, i) != m_infinity)
			{
				prev[i] = current_vertex;
				queue.push(i);
			}
		}
	}

	current_vertex = goal_vertex;
	while (prev[current_vertex] != SIZE_MAX)
	{
		path.vertices.push_back(current_vertex);
		current_vertex = prev[current_vertex];
		if (start_vertex == current_vertex)
		{
			path.vertices.push_back(current_vertex);
			break;
		}
	}

	std::reverse(path.vertices.begin(), path.vertices.end());
	path.distance = static_cast<TYPE>(path.vertices.size() - 1);
	return path;
}



template<typename TYPE>
d8::graph_path<TYPE> d8::graph<TYPE>::get_short_path(size_t start_vertex, size_t goal_vertex, pfa algorithm) const
{
	d8::graph_path<TYPE> path;

	switch (algorithm)
	{
		case d8::pfa::bfs :
		{
			path = breadth_firts_search(start_vertex, goal_vertex);
			break;
		}
		default: 
		{
			break;
		}
	}

	return path;
}