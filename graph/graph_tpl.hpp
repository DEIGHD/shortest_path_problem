#pragma once
#include "graph.hpp"
#include <vector>
#include <queue>


template<typename TYPE>
d8::graph_path<TYPE> d8::graph<TYPE>::breadth_firts_search(size_t start_vertex, size_t goal_vertex) const
{
	size_t vertices_count = m_vertices.size();
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
		for (auto & adjacent_vertex : m_vertices[current_vertex].adjacent_vertices)
		{
			if (prev[adjacent_vertex] == SIZE_MAX)
			{
				prev[adjacent_vertex] = current_vertex;
				queue.push(adjacent_vertex);
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

template<typename TYPE>
void d8::graph<TYPE>::from_weight_matrix(const d8::matrix<TYPE> & weight_matrix)
{
	size_t row_count = weight_matrix.get_row_count();
	size_t column_count = weight_matrix.get_column_count();

	m_vertices.resize(row_count);
	m_edges.clear();

	edge<TYPE> current_edge;

	for (size_t row = 0; row < row_count; row++)
	{
		for (size_t col = 0; col < column_count; col++)
		{
			if (weight_matrix(row, col) != 0 && weight_matrix(row, col) != m_infinity)
			{
				m_vertices[row].adjacent_vertices.push_back(col);

				current_edge.first_vertex = row;
				current_edge.second_vertex = col;
				current_edge.weight = weight_matrix(row, col);

				m_edges.push_back(current_edge);
			}

		}
	}
}

