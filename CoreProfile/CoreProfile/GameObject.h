#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "BaseComponents.h"

class GameObject
{
public:
  TransformComponent *transform = nullptr;
  RenderComponent *renderer = nullptr;

  GameObject();
  virtual ~GameObject();

  virtual void Update(){}
};

#endif