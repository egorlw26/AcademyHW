#pragma once

class ScopedCaller
{
public:
	typedef void(*return_f)();

	ScopedCaller(void(*func)()) : mp_caller(new Caller(func)) {};
	
	ScopedCaller(const ScopedCaller&) = delete;

	ScopedCaller(const ScopedCaller& other) noexcept
	{
		mp_caller->set(other.mp_caller->get());
	}

	ScopedCaller(ScopedCaller&& other) = delete;

	ScopedCaller& operator = (const ScopedCaller& other) noexcept
	{
		mp_caller->set(other.mp_caller->get());
		return *this;
	}

	ScopedCaller& operator = (ScopedCaller&& other) = delete;

	void Reset(void(*func)()) noexcept
	{
		if (mp_caller->get() != nullptr)
			mp_caller->call();
		mp_caller->set(func);
	};

	return_f Release() noexcept
	{
		return_f t_func = mp_caller->get();
		mp_caller->set(nullptr);
		return t_func;
	};

	~ScopedCaller()
	{
		if (mp_caller->get() != nullptr)
		{
			mp_caller->call();
			delete mp_caller;
		}
	};

private:

	struct Caller
	{
		Caller(void(*func)()) : mp_f(func) {};
		~Caller() { };
		void call() { mp_f(); };
		return_f get() const noexcept { return mp_f; }
		void set(void(*n_func) ()) noexcept { mp_f = n_func; };
	private:
		void(*mp_f) ();
	};

	Caller* mp_caller;
};
