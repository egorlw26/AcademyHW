#pragma once
#include <functional>
#include <memory>
#include <string>
#include <map>

class InterfaceFactory
{
	struct TypeBase
	{
		virtual void* GetPointer() = 0;
	};

	template<typename Type>
	struct WrapperTypeBase : TypeBase
	{
		void* GetPointer() final
		{
			return new Type();
		}
	};

public:
	template<typename TInterface>
	inline bool IsRegistered() const noexcept;

	template<typename TInterface, typename TImplementation>
	inline void Register();

	template<typename TInterface>
	inline void Register(std::function<std::unique_ptr<TInterface>()> i_create_proc);

	template<typename TInterface>
	inline void Unregister();

	template<typename TInterface>
	inline std::unique_ptr<TInterface> Create() const;

	template<typename TInterface>
	inline TInterface* CreateRaw() const;

	static InterfaceFactory& Instance();

private:
	std::map<std::string, TypeBase*> m_map;
};

template<typename TInterface>
bool InterfaceFactory::IsRegistered() const noexcept
{
	return m_map.find(typeid(TInterface).name()) != m_map.end();
}

template<typename TInterface, typename TImplementation>
void InterfaceFactory::Register()
{
	if (!Instance().IsRegistered<TInterface>())
	{
		if (std::is_base_of<TInterface, TImplementation>::value)
			m_map[typeid(TInterface).name()] = new WrapperTypeBase<TImplementation>();
		else
			throw std::exception("You've used Implementaton of wrong Interface\n");
	}
	else
		throw std::exception("You've already registered this Interface\n");
}

template<typename TInterface>
void InterfaceFactory::Register(std::function<std::unique_ptr<TInterface>()> i_create_proc)
{
	if (Instance().IsRegistered<TInterface>())
	{
		using type = std::remove_pointer<>::type;
		m_map[typeid(TInterface).name()] = new WrapperTypeBase<type>();
	}
	else
		throw std::exception("You've already registered this Interface\n");
}

template<typename TInterface>
void InterfaceFactory::Unregister()
{
	m_map.erase(typeid(TInterface).name());
}

template<typename TInterface>
std::unique_ptr<TInterface> InterfaceFactory::Create() const
{
	return std::unique_ptr<TInterface>((TInterface*)m_map.at(typeid(TInterface).name())->GetPointer());
}

template<typename TInterface>
TInterface* InterfaceFactory::CreateRaw() const
{
	return (TInterface*)m_map.at(typeid(TInterface).name())->GetPointer();
}