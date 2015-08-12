#include "RenderManager.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{

}

void RenderManager::Update()
{
  for (auto elem : rComps)
  {
    gl3wDrawBuffer(elem->type);

  }
}