#pragma once
#include "SharedPointer.h"

template<typename T>
class Weak_pointer
{
public:
	Weak_pointer();

	Weak_pointer(const Weak_pointer<T>& other);

	Weak_pointer(const Shared_pointer<T>& other);

	~Weak_pointer();

	Weak_pointer<T> operator = (const Weak_pointer<T>& other);

	Weak_pointer<T> operator = (const Shared_pointer<T>& other);

	size_t use_count() const;

	void swap(const Weak_pointer<T>& other);

	bool expired() const;

	Shared_pointer<T> lock() const;

	BlockBase<T>* getSharedPtrBlock(const Shared_pointer<T>& other);

	void setSharedPtrBlock(Shared_pointer<T>& other) const;

private:
	BlockBase<T>* mp_block;
};

template<typename T>
Weak_pointer<T>::Weak_pointer()
{
	mp_block = nullptr;
}

template<typename T>
Weak_pointer<T>::Weak_pointer(const Weak_pointer<T>& other)
{
	mp_block = other.mp_block;
	if (!expired())
		mp_block->update(1, 0);
}

template<typename T>
BlockBase<T>* Weak_pointer<T>::getSharedPtrBlock(const Shared_pointer<T>& other)
{
	return other.mp_block;
}

template<typename T>
void Weak_pointer<T>::setSharedPtrBlock(Shared_pointer<T>& other) const
{
	if (other.mp_block != nullptr)
		other.mp_block->update(0, 1);
	other.mp_block = mp_block;
	mp_block->update(1, 1);
}

template<typename T>
Weak_pointer<T>::Weak_pointer(const Shared_pointer<T>& other)
{
	mp_block = getSharedPtrBlock(other);
	if (!expired())
		mp_block->update(1, 0);
}

template<typename T>
Weak_pointer<T>::~Weak_pointer()
{
	if (!expired())
		mp_block->update(0, 0);
	mp_block = nullptr;
}

template<typename T>
Weak_pointer<T> Weak_pointer<T>::operator=(const Weak_pointer<T>& other)
{
	mp_block = other.mp_block;
	if (!expired())
		mp_block->update(1, 0);
	return *this;
}

template<typename T>
Weak_pointer<T> Weak_pointer<T>::operator=(const Shared_pointer<T>& other)
{
	mp_block = getSharedPtrBlock(other);
	if (!expired())
		mp_block->update(1, 0);
	return *this;
}

template<typename T>
size_t Weak_pointer<T>::use_count() const
{
	return mp_block->getSharedCount();
}

template<typename T>
void Weak_pointer<T>::swap(const Weak_pointer<T>& other)
{
	mp_block->update(0, 0);
	mp_block = other.mp_block;
	mp_block->update(1, 0);
}

template<typename T>
bool Weak_pointer<T>::expired() const
{
	return mp_block == nullptr;
}

template<typename T>
Shared_pointer<T> Weak_pointer<T>::lock() const
{
	Shared_pointer<T> ans;
	setSharedPtrBlock(ans);
	return ans;
}