#pragma once
#include<utility>
#include<type_traits>

template<typename T>
class Matrix
{
public:
	Matrix(const size_t row, const size_t column);

	~Matrix();

	Matrix(const Matrix<T>& other);

	Matrix(Matrix<T>&& other);

	Matrix<T> operator = (const Matrix<T>& other);

	Matrix<T> operator = (Matrix<T>&& other);

	template<typename U>
	Matrix<T> operator = (const Matrix<U>& other);

	template<typename U>
	Matrix<T> operator = (Matrix<U>&& other);

	Matrix<T> operator = (const std::initializer_list<T>& list);

	T& operator [](const size_t pos);

	const T& operator [](const size_t pos) const;

	const size_t getRows() const;

	const size_t getColumns() const;

	T* getCells();

	const T* getCells() const;

	template<typename U>
	Matrix<decltype(std::declval<T>() + std::declval<U>())> operator + (const Matrix<U>& other) const;

	template<typename U>
	Matrix<decltype(std::declval<T>() + std::declval<U>())> operator + (const U& value) const;

	template<typename U>
	Matrix<decltype(std::declval<T>() + std::declval<U>())> operator - (const U& value) const;

	Matrix<T> operator - () const;

	template<typename U>
	Matrix<decltype(std::declval<T>() + std::declval<U>())> operator - (const Matrix<U>& other) const;

	/*template<typename U>
	Matrix<decltype(std::declval<T>() + std::declval<U>())> operator * (const Matrix<U>& other) const;*/

private:
	size_t m_rows;
	size_t m_columns;
	T* mp_cells;
};




template<typename T>
Matrix<T>::Matrix(const size_t row, const size_t column)
	: m_rows(row)
	, m_columns(column)
	, mp_cells((T*)malloc(m_rows * m_columns * sizeof(T)))
{
	static_assert((std::is_integral<T>::value || std::is_floating_point<T>::value), "Need integral or floating");
}

template<typename T>
Matrix<T>::~Matrix()
{
	delete[] mp_cells;
	mp_cells = nullptr;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
	m_rows = other.m_rows;
	m_columns = other.m_columns;
	mp_cells = (T*)new char[m_rows * m_columns * sizeof(T)];
	for (size_t i = 0; i < m_rows * m_columns; ++i)
		mp_cells[i] = other.mp_cells[i];
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other)
{
	m_rows = other.m_rows;
	m_columns = other.m_columns;
	other.m_rows = 0;
	other.m_columns = 0;
	mp_cells = other.mp_cells;
	other.mp_cells = nullptr;
}


template<typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T>& other)
{
	if (this != &other)
	{
		m_rows = other.m_rows;
		m_columns = other.m_columns;
		mp_cells = new char[m_rows * m_columns * sizeof(T)];
		for (size_t i = 0; i < m_rows * m_columns; ++i)
			mp_cells[i] = other.mp_cells[i];
		return *this;
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator=(Matrix<T>&& other)
{
	if (this != &other)
	{
		m_rows = other.m_rows;
		m_columns = other.m_columns;
		other.m_rows = 0;
		other.m_columns = 0;
		mp_cells = other.mp_cells;
		other.mp_cells = nullptr;
		return *this;
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator=(const std::initializer_list<T>& list)
{
	if (list.size() != m_rows * m_columns)
		throw 1;
	for (size_t i = 0; i < list.size(); ++i)
		mp_cells[i] = *(list.begin() + i);
	return *this;
}

template<typename T>
T& Matrix<T>::operator[](const size_t pos)
{
	return mp_cells[pos];
}

template<typename T>
const T& Matrix<T>::operator[](const size_t pos) const
{
	return mp_cells[pos];
}

template<typename T>
const size_t Matrix<T>::getRows() const
{
	return m_rows;
}

template<typename T>
const size_t Matrix<T>::getColumns() const
{
	return m_columns;
}

template<typename T>
T* Matrix<T>::getCells()
{
	return mp_cells;
}

template<typename T>
const T* Matrix<T>::getCells() const
{
	return mp_cells;
}

template<typename T>
template<typename U>
Matrix<T> Matrix<T>::operator=(const Matrix<U>& other)
{
	if (this != &other)
	{
		m_rows = other.m_rows;
		m_columns = other.m_columns;
		mp_cells = new char(m_rows * m_columns * sizeof(T));
		for (size_t i = 0; i < m_rows * m_columns; ++i)
			mp_cells[i] = static_cast<T>(other.mp_cells[i]);
		return *this;
	}
}

template<typename T>
template<typename U>
Matrix<T> Matrix<T>::operator=(Matrix<U>&& other)
{
		m_rows = other.m_rows;
		m_columns = other.m_columns;
		other.m_rows = 0;
		other.m_columns = 0;
		mp_cells = (T*)new char[m_rows * m_columns * sizeof(T)];
		for (size_t i = 0; i < m_rows * m_columns; ++i)
			mp_cells[i] = static_cast<T>(std::move(other.mp_cells[i]));
		other.mp_cells = nullptr;
		return *this;
}

template<typename T>
template<typename U>
Matrix<decltype(std::declval<T>() + std::declval<U>())> Matrix<T>::operator + (const Matrix<U>& rs) const
{
	if (rs.getRows() != m_rows || rs.getColumns() != m_columns)
		throw 1;
	Matrix<decltype(std::declval<T>() + std::declval<U>())> ans(m_rows, m_columns);
	for (size_t i = 0; i < m_rows * m_columns; ++i)
		ans.getCells()[i] = mp_cells[i] + rs.getCells()[i];
	return ans;
}

template<typename T>
template<typename U>
Matrix<decltype(std::declval<T>() + std::declval<U>())> Matrix<T>::operator + (const U& value) const
{
	Matrix<decltype(std::declval<T>() + std::declval<U>())> ans(m_rows, m_columns);
	for (size_t i = 0; i < m_rows * m_columns; ++i)
		ans.getCells()[i] = mp_cells[i] + value;
	return ans;
}

template<typename T>
template<typename U>
Matrix<decltype(std::declval<T>() + std::declval<U>())> Matrix<T>::operator - (const U& value) const
{
	return (*this) + (-value);
}

template<typename T>
Matrix<T> Matrix<T>::operator - () const
{
	Matrix<T> ans = *this;
	for (size_t i = 0; i < m_rows * m_columns; ++i)
		ans.mp_cells[i] *= -1;
	return ans;
}

template<typename T>
template<typename U>
Matrix<decltype(std::declval<T>() + std::declval<U>())> Matrix<T>::operator- (const Matrix<U>& other) const
{
	return (*this) - other;
}

//template<typename T>
//template<typename U>
//Matrix<decltype(std::declval<T>() + std::declval<U>())> Matrix<T>::operator * (const Matrix<U>& other) const
//{
//	Matrix<decltype(std::declval<T>() + std::declval<U>())> ans(m_rows, other.getColumns());
//
//}