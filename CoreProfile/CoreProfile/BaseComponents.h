#ifndef BASE_COMP_H
#define BASE_COMP_H

#include <vector>
#include <algorithm>
#include "MathExt.h"

struct IComponent
{
  unsigned ID;
};

struct RenderComponent : public IComponent
{
  unsigned int type;
  std::vector<Vec2> mesh;

  //std::vector<std::string> textures;
  //std::vector<std::string> shaders;

  //void BindShader(std::string name);
  //void UnBindShader(std::string name);
};

struct TransformComponent : public IComponent
{
  //Vec3 position;
  //X , Y , Depth
  Vec3 position;
  Vec2 scale;

  float rotation;
  //float Depth
};

#endif