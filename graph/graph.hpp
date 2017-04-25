#pragma once
#include "..\matrix\matrix.hpp"
#include "graph_path.hpp"
#include <list>
#include <string>
#include <memory>
#include <functional>

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
		template<typename TYPE>
		class vertex
		{
		public:
			std::list< size_t > adjacent_vertices;
			std::string name = "";
		};
		template<typename TYPE>
		class edge
		{
		public:
			size_t first_vertex;
			size_t second_vertex;
			TYPE weight;
			bool has_direction = false;
		};

		std::vector< vertex<TYPE> > m_vertices;
		std::vector< edge<TYPE> > m_edges;
		TYPE m_infinity;



		d8::graph_path<TYPE> breadth_firts_search(size_t start_vertex, size_t goal_vertex) const;
	public:
		using value_type = TYPE;

		graph() 
		{
			set_infinity_default();
		};

		graph(const size_t vertices_count) noexcept
		{
			m_vertices.resize(vertices_count);
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

		inline std::list<size_t> get_adjacent_vertices(size_t vertex) const
		{
			return m_vertices[vertex].adjacent_vertices;
		}

		void from_weight_matrix(const matrix<TYPE> & weight_matrix);

		inline void from_adjacency_matrix(const matrix<TYPE> & adjacency_matrix)
		{
			from_weight_matrix(adjacency_matrix);
		}
		
		graph_path<TYPE> get_short_path(size_t start_vertex, size_t goal_vertex, pfa algorithm) const;
	};

}

#include "graph_tpl.hpp"
