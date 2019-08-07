#pragma once


struct IAction
{
	virtual void DoSomething() = 0;
};

struct Action : public IAction
{
	virtual void DoSomething();
};