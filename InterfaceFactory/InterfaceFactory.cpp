
#include "InterfaceFactory.h"



InterfaceFactory& InterfaceFactory::Instance()
{
	static InterfaceFactory m_if;
	return m_if;
}
