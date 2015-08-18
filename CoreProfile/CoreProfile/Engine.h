#ifndef ENGINE_H
#define ENGINE_H

#include "RenderManager.h"
#include "GLWrapper.h"

class GameEngine
{
  RenderManager rMan;
  InputManager iMan;

public:
  GameEngine(){}
  ~GameEngine(){}

  void setup()
  {

  }
  void Update()
  {
  }

  void Render(){ rMan.Update(); }
};

#endif;
