#pragma once

template<typename T>
class MyVector
{

public:
	MyVector(const size_t capacity = 10);

	~MyVector();

	MyVector(const MyVector<T>& other);

	MyVector(MyVector<T>&& other);

	MyVector& operator = (const MyVector& other);

	MyVector& operator = (MyVector&& other);

	const size_t size() const;

	T& at(const size_t pos);

	const T& at(const size_t pos) const;

	T& operator [] (const size_t pos);

	const T& operator [] (const size_t pos) const;

	const bool empty() const;

	T& front();

	const T& front() const;

	T& back();

	const T& back() const;

	void push_back(const T& item);

	void push_back(T&& item);

	template<typename... Args>
	void emplace_back(Args&&... args);

	void pop_back();

	void reserve(const size_t n_capacity = 10);

	template<typename Func>
	void for_each(const Func& i_func);

private:
	size_t m_capacity;
	size_t m_size;
	T* mp_array;
};

template<typename T>
MyVector<T>::MyVector(const size_t capacity = 10)
	: m_capacity(capacity), m_size(0), mp_array((T*)malloc(capacity*sizeof(T)))
{

}

template<typename T>
MyVector<T>::~MyVector()
{
	delete[] mp_array;
	mp_array = nullptr;
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	mp_array = new char(m_capacity * sizeof(T));
	for (size_t i = 0; i < m_size; ++i)
		mp_array[i] = other.mp_array[i];
}

template<typename T>
MyVector<T>::MyVector(MyVector<T>&& other)
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	other.m_capacity = 0;
	other.m_size = 0;
	mp_array = other.mp_array;
	other.mp_array = nullptr;
}

template<typename T>
MyVector<T>& MyVector<T>::operator= (const MyVector<T>& other)
{
	if (this != &other)
	{
		m_capacity = other.m_capacity;
		m_size = other.m_size;
		mp_array = new char[m_capacity * sizeof(T)];
		for (size_t i = 0; i < m_size; ++i)
			mp_array[i] = other.mp_array[i];
		return *this;
	}
}

template<typename T>
MyVector<T>& MyVector<T>::operator= (MyVector<T>&& other)
{
	if (this != &other)
	{
		m_capacity = other.m_capacity;
		m_size = other.m_size;
		other.m_capacity = 0;
		other.m_size = 0;
		mp_array = other.mp_array;
		other.mp_array = nullptr;
		return *this;
	}
}

template<typename T>
const size_t MyVector<T>::size() const
{
	return m_size;
}

template<typename T>
T& MyVector<T>::at(const size_t pos)
{
	const MyVector<T>& self = *this;
	return const_cast<T&>(self.at(pos));
}

template<typename T>
const T& MyVector<T>::at(const size_t pos) const
{
	if (pos > m_size)
		throw 1;
	return mp_array[pos];
}

template<typename T>
T& MyVector<T>::operator[] (const size_t pos)
{
	const MyVector<T>& self = *this;
	return const_cast<T&>(self[pos]);
}

template<typename T>
const T& MyVector<T>::operator[] (const size_t pos) const
{
	return mp_array[pos];
}

template<typename T>
const bool MyVector<T>::empty() const
{
	return (!m_size);
}

template<typename T>
T& MyVector<T>::front()
{
	const MyVector<T>& self = *this;
	return const_cast<T&>(self.front());
}

template<typename T>
const T& MyVector<T>::front() const
{
	if (empty())
		throw 1;
	return mp_array[0];
}

template<typename T>
T& MyVector<T>::back()
{
	const MyVector<T>& self = *this;
	return const_cast<T&>(self.back());
}

template<typename T>
const T& MyVector<T>::back() const
{
	if (empty())
		throw 1;
	return mp_array[m_size - 1];
}

template<typename T>
void MyVector<T>::push_back(const T& item)
{
	if (m_capacity == m_size)
		reserve(m_capacity * 2);
	mp_array[m_size] = item;
	++m_size;
}

template<typename T>
void MyVector<T>::push_back(T&& item)
{
	if (m_capacity == m_size)
		reserve(m_capacity * 2);
	mp_array[m_size] = std::move(item);
	++m_size;
}

template<typename T>
template<class... Args>
void MyVector<T>::emplace_back(Args&&... args)
{
	push_back(T(std::forward<Args>(args)...));
}

template<typename T>
void MyVector<T>::pop_back()
{
	if (empty())
		throw 1;
	T t = std::move(mp_array[m_size - 1]);
	--m_size;
}

template<typename T>
void MyVector<T>::reserve(const size_t n_capacity)
{
	if (n_capacity < m_size)
		throw 1;
	m_capacity = n_capacity;
	T* tp_array = (T*)new char[n_capacity * sizeof(T)];
	for (size_t i = 0; i < m_size; ++i)
		tp_array[i] = std::move(mp_array[i]);
	T* t = mp_array;
	mp_array = tp_array;
	delete[] t;
}

template<typename T>
template<typename Func>
void MyVector<T>::for_each(const Func& i_func)
{
	for (size_t i = 0; i < m_size; ++i)
		i_func(mp_array[i]);
}