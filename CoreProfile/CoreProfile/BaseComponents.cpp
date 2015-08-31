#include "BaseComponents.h"

//-------------------------------------------------------------
// COMPONENT MANAGER
//-------------------------------------------------------------
ICompManager* ICompManager::m_inst = nullptr;
ICompManager* ICompManager::Inst()
{
  if (!m_inst) m_inst = new ICompManager();
  return m_inst;
}

void ICompManager::AddTransfCmp(TransformComponent* cmp)
{
  tComps.push_back(cmp);
}

void ICompManager::AddRenderCmp(RenderComponent* cmp)
{
  rComps.push_back(cmp);
}

void ICompManager::AddShaderCmp(ShaderComponent* cmp)
{
  sComps.push_back(cmp);
}


//-------------------------------------------------------------
//-------------------------------------------------------------
// COMPONENT
//-------------------------------------------------------------

unsigned IComponent::m_Counter = 0;

IComponent::IComponent() : m_ID(m_Counter++){}

unsigned IComponent::GetID() const { return m_ID; }

//-------------------------------------------------------------
//-------------------------------------------------------------
// RENDER COMPONENT
//-------------------------------------------------------------

RenderComponent::RenderComponent(const std::string& texturename) : m_TextureID(LoadTexture(texturename))
{ SetColor(Vec3(1, 1, 1)); }

RenderComponent::RenderComponent() : m_TextureID(-1)
{ SetColor(Vec3(1,1,1)); }

RenderComponent::RenderComponent(const Vector3D& col) : m_TextureID(-1)
{ SetColor(col); }

RenderComponent::RenderComponent(float r, float g, float b) : m_TextureID(-1)
{ SetColor(Vec3(r, g, b)); }

//Load Texture Manually
int RenderComponent::LoadTexture(const std::string& texturename)
{
  //Load Texture Function Here!
	return -1;
}

void RenderComponent::SetColor(const Vector3D& col)
{
	m_Color = col;
}

int RenderComponent::GetTextureID() const { return m_TextureID; }

Vector3D& RenderComponent::GetColor() { return m_Color; }

//-------------------------------------------------------------
//-------------------------------------------------------------
// TRANSFORM COMPONENT
//-------------------------------------------------------------
TransformComponent::TransformComponent() : m_scale(Vec2(1,1))
{}

void TransformComponent::SetPosition(const Vector3D& pos)
{
  m_position = pos;
}

void TransformComponent::SetPosition(float x, float y, float z)
{
  SetPosition(Vec3(x, y, z));
}

void TransformComponent::SetRotation(const Vector3D& rot)
{
  m_rotation = rot;
}

void TransformComponent::SetRotation(float x, float y, float z)
{
  SetRotation(Vec3(x, y, z));
}

void TransformComponent::SetSize(float x, float y)
{
  m_scale.x = x; m_scale.y = y;
}

Vector3D TransformComponent::GetPosition(){ return m_position; }
Vector3D TransformComponent::GetRotation(){ return m_rotation; }
Vector2D TransformComponent::GetScale(){ return m_scale; }

//-------------------------------------------------------------