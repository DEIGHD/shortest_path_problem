#pragma once
#include <vector>

namespace d8
{

	template<typename TYPE>
	class graph_path
	{
	public:
		using value_type = TYPE;

		graph_path() {};

		graph_path(graph_path && right) noexcept
		{
			std::swap(vertices, right.vertices);
			std::swap(distance, right.distance);
		}

		graph_path(graph_path & right) noexcept
		{
			vertices = right.vertices;
			distance = right.distance;
		}

		const graph_path & operator=(graph_path && right) noexcept
		{
			std::swap(vertices, right.vertices);
			std::swap(distance, right.distance);
			return *this;
		}

		const graph_path & operator=(graph_path & right) noexcept
		{
			vertices = right.vertices;
			distance = right.distance;
			return *this;
		}

		std::vector<size_t> vertices;
		TYPE distance;
	};

}
