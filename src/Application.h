#pragma once

#include "Actor.h"

class Application : public Actor
{
private:
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
};

