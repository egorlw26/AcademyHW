#pragma once
#include <functional>
#include <memory>
#include <string>
#include <map>

class InterfaceFactory
{
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
	std::map<> m_map; //Need to save interface & implement
};
