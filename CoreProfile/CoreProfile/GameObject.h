#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "BaseComponents.h"

class vObject
{
	virtual void Update() = 0;
};

class BaseObject : public vObject
{
public:
  unsigned tID;
  unsigned rID;

  BaseObject();

  void Update();
};

#endif