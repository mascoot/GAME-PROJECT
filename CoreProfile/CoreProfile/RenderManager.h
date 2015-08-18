#ifndef REN_MAN_H
#define REN_MAN_H

#include "GameObject.h"
#include "gl/gl3w.h"
#include "GLWrapper.h"
#include "Shader.h"

class RenderManager
{
  GLuint vertexbuffer;  // This will identify our vertex buffer
  GLuint indicesbuffer;
  GLuint uvbuffer;

  std::vector<unsigned int> indices;

  std::vector<RenderComponent*> rComps;
  ShaderProgram *gProgram;

  void LoadShaders();
public:

  RenderManager();
  ~RenderManager();

  void Update();
};

#endif