#pragma once

template<typename T>
class BlockBase
{
public:
	
	BlockBase();

	virtual T& get() = 0;

	virtual void update(bool generated, bool shared) = 0;

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

	virtual void update(bool generated, bool shared) override;

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
void BlockSeparate<T>::update(bool generated, bool shared)
{
	if (generated)
		shared ? ++this->shared_counter: ++this->weak_counter;
	else
		shared ? --this->shared_counter : --this->weak_counter;

	if (this->shared_counter == 0 && this->weak_counter != 0)
	{
		delete mp_data;
		mp_data = nullptr;
	}

	if (this->shared_counter == 0 && this->weak_counter == 0)
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

	virtual void update(bool generated, bool shared) override;

private:
	T m_data;
};

template<typename T>
template<typename... Args>
BlockNear<T>::BlockNear(Args&&... args)
{
	m_data = T(args...);
}

template<typename T>
BlockNear<T>::~BlockNear()
{
	~T();
}

template<typename T>
T& BlockNear<T>::get()
{
	return m_data;
}

template<typename T>
void BlockNear<T>::update(bool generated, bool shared)
{
	if (generated)
		shared ? ++this->shared_counter : ++this->weak_counter;
	else
		shared ? --this->shared_counter : --this->weak_counter;

	if (this->shared_counter == 0 && this->weak_counter == 0)
		delete this;
	if (this->shared_counter == 0 && this->weak_counter != 0)
		~T();
}