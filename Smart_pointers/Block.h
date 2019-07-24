#pragma once

template<typename T>
class BlockBase
{
public:

	BlockBase();

	virtual T& get() = 0;

	virtual void check() = 0;

	void updateShared(bool increase);

	void updateWeak(bool increase);

	virtual ~BlockBase();

	size_t getSharedCount() const;

	size_t getWeakCount() const;

protected:
	size_t shared_counter = 0;
	size_t weak_counter = 0;
};

template<typename T>
BlockBase<T>::BlockBase()
{ }

template<typename T>
void BlockBase<T>::updateShared(bool increase)
{
	increase ? ++(this->shared_counter) : --(this->shared_counter);
	if (shared_counter == 0)
		check();
}

template<typename T>
void BlockBase<T>::updateWeak(bool increase)
{
	increase ? ++(this->weak_counter) : --(this->weak_counter);
	if (weak_counter == 0)
		check();
}

template<typename T>
BlockBase<T>::~BlockBase()
{ }

template<typename T>
size_t BlockBase<T>::getSharedCount() const
{
	return shared_counter;
}

template<typename T>
size_t BlockBase<T>::getWeakCount() const
{
	return weak_counter;
}


//BlockSeparate




template<typename T>
class BlockSeparate : public BlockBase<T>
{
public:
	BlockSeparate();

	BlockSeparate(T* data);

	virtual ~BlockSeparate() override;

	virtual T& get() override;

	virtual void check() override;

private:
	T* mp_data;
};

template<typename T>
BlockSeparate<T>::BlockSeparate()
{
	mp_data = nullptr;
}

template<typename T>
BlockSeparate<T>::BlockSeparate(T* data)
{
	mp_data = data;
}

template<typename T>
BlockSeparate<T>::~BlockSeparate()
{
	if (mp_data != nullptr)
		delete mp_data;
}

template<typename T>
T& BlockSeparate<T>::get()
{
	return *mp_data;
}

template<typename T>
void BlockSeparate<T>::check()
{
	if (shared_counter == 0 && weak_counter != 0)
	{
		delete mp_data;
		mp_data = nullptr;
	}
	if (shared_counter == 0 && weak_counter == 0)
		delete this;
}





//BlockNear



template<typename T>
class BlockNear : public BlockBase<T>
{
public:

	template<typename... Args>
	BlockNear(Args&&... args);

	virtual ~BlockNear() override;

	virtual T& get() override;

	virtual void check() override;

private:
	T m_data;
};

template<typename T>
template<typename... Args>
BlockNear<T>::BlockNear(Args&&... args)
{
	m_data = T(std::forward<Args>(args...));
}

template<typename T>
BlockNear<T>::~BlockNear()
{ }

template<typename T>
T& BlockNear<T>::get()
{
	return m_data;
}

template<typename T>
void BlockNear<T>::check()
{
	if (shared_counter == 0 && weak_counter != 0)
		m_data.~T();
	if (shared_counter == 0 && weak_counter == 0)
		delete this;
}