#pragma once
#include "..\matrix\matrix.hpp"
#include "graph_path.hpp"

namespace d8
{

	enum class pfa //path_finding_algorithms
	{
		bfs, //breadth_firts_search
	};

	template<typename TYPE>
	class graph
	{
	private:
		d8::matrix<TYPE> m_weight_matrix;
		TYPE m_infinity;

		graph_path<TYPE> breadth_firts_search(size_t start_vertex, size_t goal_vertex) const;
	public:
		using value_type = TYPE;

		graph() 
		{
			set_infinity_default();
		};

		graph(const size_t vertices_count) noexcept
		{
			m_weight_matrix.resize(vertices_count, vertices_count);
			m_weight_matrix.set(0);
			set_infinity_default();
		}

		inline void set_infinity(const TYPE value) noexcept
		{
			m_infinity = value;
		}

		inline void set_infinity_default() noexcept
		{
			if (std::is_floating_point<TYPE>::value)
			{
				m_infinity = INFINITY;
			}
			else
			{
				m_infinity = std::numeric_limits<TYPE>::max();
			}
		}

		inline TYPE get_infinity() const noexcept
		{
			return m_infinity;
		}

		inline std::vector<size_t> get_adjacent_vertices(size_t vertex) const
		{
			size_t adjacent_vertex;
			size_t vertices_count = m_weight_matrix.get_column_count();
			std::vector<size_t> adjacent_vertices;

			for (adjacent_vertex = 0; adjacent_vertex < vertices_count; adjacent_vertex++)
			{
				if (m_weight_matrix(vertex, adjacent_vertex) != 0 && m_weight_matrix(vertex, adjacent_vertex) != m_infinity)
				{
					adjacent_vertices.push_back(adjacent_vertex);
				}
			}

			return adjacent_vertices;
		}

		inline void from_weight_matrix(const matrix<TYPE> & weight_matrix)
		{
			m_weight_matrix = weight_matrix;
		}

		inline void from_adjacency_matrix(const matrix<TYPE> & adjacency_matrix)
		{
			size_t row_count = m_weight_matrix.get_row_count();
			size_t column_count = m_weight_matrix.get_column_count();

			m_weight_matrix.resize(row_count, column_count);

			for (size_t row = 0; row < row_count; row++)
			{
				for (size_t col = 0; col < column_count; col++)
				{
					if (row != col && adjacency_matrix(row, col) == 0)
					{
						m_weight_matrix(row, col) = m_infinity;
					}
					else
					{
						m_weight_matrix(row, col) = adjacency_matrix(row, col);
					}
				}
			}
		}
		
		graph_path<TYPE> get_short_path(size_t start_vertex, size_t goal_vertex, pfa algorithm) const;
	};

}

#include "graph_tpl.hpp"
