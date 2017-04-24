#pragma once
#include <vector>
#include <exception>

namespace d8
{
	template <typename TYPE>
	class matrix
	{
	private:
		std::vector< std::vector<TYPE> > m_data;
		size_t m_row_count = 0;
		size_t m_column_count = 0;
	public:
		using value_type = TYPE;

		matrix() {}

		matrix(size_t row_count, size_t column_count) noexcept
		{
			m_data.resize(row_count, std::vector<TYPE>(column_count));
			m_row_count = row_count;
			m_column_count = column_count;
		}

		inline void set(const TYPE & value)
		{
			for (size_t row = 0; row < m_row_count; row++)
			{
				for (size_t col = 0; col < m_column_count; col++)
				{
					m_data[row][col] = value;
				}
			}
		}

		inline void clear(size_t row_count, size_t column_count) noexcept
		{
			m_data.clear();
			m_row_count = 0;
			m_column_count = 0;
		}

		inline TYPE & operator()(size_t i, size_t j)
		{
			if (i >= m_row_count || j >= m_column_count)
			{
				throw exception::out_of_range();
			}
			else
			{
				return m_data[i][j];
			}
		}

		inline const TYPE & operator()(size_t i, size_t j) const
		{
			if (i >= m_row_count || j >= m_column_count)
			{
				throw exception::out_of_range();
			}
			else
			{
				return m_data[i][j];
			}
		}

		inline size_t get_row_count() const noexcept
		{
			return m_row_count;
		}

		inline size_t get_column_count() const noexcept
		{
			return m_column_count;
		}

		inline bool is_empty() const noexcept
		{
			if (m_row_count == 0 || m_column_count == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		matrix(const matrix & right) noexcept
		{
			m_data = right.m_data;
			m_column_count = right.m_column_count;
			m_row_count = right.m_row_count;
		}

		matrix(matrix && right) noexcept
		{
			swap(*this, right);
		}

		const matrix & operator=(const matrix & right) noexcept
		{
			m_data = right.m_data;
			m_column_count = right.m_column_count;
			m_row_count = right.m_row_count;
			return *this;
		}

		const matrix & operator=(matrix && right) noexcept
		{
			swap(*this, right);

			return *this;
		}

		const matrix & operator=(const std::vector<std::vector<TYPE>> & right)
		{
			m_data = right;

			m_data.resize(m_row_count);
			for (size_t row = 0; row < m_row_count; row++)
			{
				m_data[row].resize(m_column_count);
			}

			return (*this);
		}

		inline void resize(size_t row_count, size_t column_count)
		{
			m_row_count = row_count;
			m_column_count = column_count;

			m_data.resize(m_row_count);
			for (size_t row = 0; row < m_row_count; row++)
			{
				m_data[row].resize(m_column_count);
			}
		}

		friend void swap(matrix<TYPE> & a_matrix, matrix<TYPE> & b_matrix) noexcept
		{
			std::swap(a_matrix.m_data, b_matrix.m_data);
			std::swap(a_matrix.m_column_count, b_matrix.m_column_count);
			std::swap(a_matrix.m_row_count, b_matrix.m_row_count);
		}
	};

	namespace exception
	{
		class out_of_range : public std::exception
		{
		public:
			const char* what() const noexcept
			{
				return "out of range";
			}
		};
	}
}
