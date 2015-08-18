#ifndef REN_MAN_H
#define REN_MAN_H

#include "GameObject.h"
#include "gl/gl3w.h"

class RenderManager
{
  GLuint vertexbuffer;  // This will identify our vertex buffer
  GLuint indicesbuffer;

  std::vector<unsigned int> indices;

  std::vector<RenderComponent*> rComps;
public:
  RenderManager();
  ~RenderManager();

  void Update();
};

#endif