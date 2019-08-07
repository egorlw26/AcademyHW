#include "InterfaceFactory.h"

template<typename TInterface>
inline bool InterfaceFactory::IsRegistered() const noexcept
{
	return Instance().m_map.find(typeid(TInterface)) != Instance().m_map.end();
}

template<typename TInterface, typename TImplementation>
inline void InterfaceFactory::Register()
{
	if (!Instance().IsRegistered<TInterface>())
		Instance().m_map[typeid(TInterface)] = typeid(TImplementation);
	else
		throw std::exception("You've registered it begore");
}

template<typename TInterface>
inline void InterfaceFactory::Register(std::function<std::unique_ptr<TInterface>()> i_create_proc)
{
}

template<typename TInterface>
inline void InterfaceFactory::Unregister()
{
	if (Instance().IsRegistered<TInterface>())
		Instance().m_map.erase(typeid(TInterface));
}

template<typename TInterface>
inline std::unique_ptr<TInterface> InterfaceFactory::Create() const
{

}

template<typename TInterface>
inline TInterface* InterfaceFactory::CreateRaw() const
{

}
