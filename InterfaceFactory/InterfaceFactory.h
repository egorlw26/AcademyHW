#pragma once
#include <functional>
#include <memory>
#include <map>

class InterfaceFactory
{
	template<typename TInterface>
	inline bool IsRegistered() const;

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
	std::map<std::type_info, std::type_info> m_map;
};

InterfaceFactory& InterfaceFactory::Instance()
{
	InterfaceFactory m_if;
	return m_if;
}