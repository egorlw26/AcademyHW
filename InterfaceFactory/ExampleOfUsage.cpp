#include <iostream>
#include "Action.h"
#include "InterfaceFactory.h"



int main()
{
	InterfaceFactory::Instance().Register<IAction, Action>();
	InterfaceFactory::Instance().Unregister<IAction>();
	{
		InterfaceFactory::ScopeRegister sr;
		InterfaceFactory::Instance().Register<IAction, Action>(sr);
		InterfaceFactory::Instance().CreateRaw<IAction>()->DoSomething();
	}

	std::cout << InterfaceFactory::Instance().IsRegistered<IAction>() << std::endl;


	system("pause");
	return 0;
}