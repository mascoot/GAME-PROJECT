#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "BaseComponents.h"

class BaseObject
{
	virtual void Update() = 0;
};

class TestObject : public BaseObject
{
public:
  TransformComponent *transform = nullptr;
  RenderComponent *renderer = nullptr;

  TestObject();
  ~TestObject();

  void Update();
};

#endif