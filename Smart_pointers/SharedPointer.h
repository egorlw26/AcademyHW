#pragma once
#include "Block.h"

template<typename T>
class Weak_pointer;

template<typename T>
class Shared_pointer
{
public:
	Shared_pointer();

	Shared_pointer(T* data);

	Shared_pointer(const Shared_pointer<T>& other);

	template<typename... Args, typename = std::enable_if_t<!std::is_convertible_v<Args..., Shared_pointer<T>>>>
	Shared_pointer(Args&&... args);

	Shared_pointer<T> operator = (const Shared_pointer<T>& other);

	friend BlockBase<T>* Weak_pointer<T>::getSharedPtrBlock(const Shared_pointer<T>& other);

	friend void Weak_pointer<T>::setSharedPtrBlock(Shared_pointer<T>& other) const;
	~Shared_pointer();

	T& operator *() const;

	T* get() const;

	template<typename U, class... Args>
	friend Shared_pointer<U> make_shared(Args&&... args);

private:
	BlockBase<T>* mp_block;
};

template<typename T>
Shared_pointer<T>::Shared_pointer()
	: mp_block(nullptr)
{
}

template<typename T>
Shared_pointer<T>::Shared_pointer(T* data)
{
	mp_block = new BlockSeparate<T>(data);
	mp_block->updateShared(true);
}

template<typename T>
Shared_pointer<T>::Shared_pointer(const Shared_pointer<T>& other)
	: mp_block(other.mp_block)
{
	if (mp_block != nullptr)
		mp_block->updateShared(true);
}

template<typename T>
template<typename... Args, typename = std::enable_if_t<!std::is_convertible_v<Args..., Shared_pointer<T>>>>
Shared_pointer<T>::Shared_pointer(Args&&... args) 
	: mp_block(new BlockNear<T>(std::forward<Args>(args)...))
{
	mp_block->updateShared(true);
}

template<typename T>
Shared_pointer<T> Shared_pointer<T>::operator=(const Shared_pointer<T>& other)
{
	if (mp_block != nullptr)
		mp_block->updateShared(false);
	mp_block = other.mp_block;
	mp_block->updateShared(true);
	return *this;
}

template<typename T>
Shared_pointer<T>::~Shared_pointer()
{
	mp_block->updateShared(false);
	mp_block = nullptr;
}

template<typename T>
T& Shared_pointer<T>::operator * () const
{
	return *mp_block->get();
}

template<typename T>
T* Shared_pointer<T>::get() const
{
	return mp_block->get();
}

template<typename U, class... Args>
Shared_pointer<U> make_shared(Args&&... args)
{
	/*Shared_pointer<U> sp;
	sp.mp_block = new BlockNear<U>(std::forward<Args>(args)...);
	sp.mp_block->updateShared(true);
	return sp;*/
	return Shared_pointer<U>(std::forward<Args>(args)...);
}