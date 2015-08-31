#include "BaseComponents.h"

//-------------------------------------------------------------
// COMPONENT MANAGER
//-------------------------------------------------------------
ICompManager* ICompManager::m_inst = new ICompManager();

ICompManager* ICompManager::Inst() { return m_inst; }

unsigned ICompManager::AddTransfCmp()
{
  tComps.push_back(TransformComponent());
  return tComps.size() - 1;
}

unsigned ICompManager::AddRenderCmp()
{
  rComps.push_back(RenderComponent());
  return rComps.size() - 1;
}

unsigned ICompManager::AddShaderCmp()
{
  sComps.push_back(ShaderComponent());
  return sComps.size() - 1;
}

TransformComponent& ICompManager::GetTransfCmp(unsigned index)
{
  return tComps[index];
}

RenderComponent& ICompManager::GetRenderCmp(unsigned index)
{
  return rComps[index];
}

ShaderComponent& ICompManager::GetShaderCmp(unsigned index)
{
  return sComps[index];
}

//-------------------------------------------------------------
//-------------------------------------------------------------
// COMPONENT
//-------------------------------------------------------------

IComponent::IComponent() : m_ID(0){}

void IComponent::SetID(unsigned id){ m_ID = id; }

unsigned IComponent::GetID() const { return m_ID; }

void IComponent::SetActive(bool a) { m_isActive = a; }

bool IComponent::IsActive() const { return m_isActive; }

//-------------------------------------------------------------
//-------------------------------------------------------------
// RENDER COMPONENT
//-------------------------------------------------------------

RenderComponent::RenderComponent(const std::string& texturename) : m_TextureID(LoadTexture(texturename))
{ SetColor(Vec4(1, 1, 1, 1)); }

RenderComponent::RenderComponent() : m_TextureID(-1)
{ SetColor(Vec4(1, 1, 1, 1)); }

RenderComponent::RenderComponent(const Vector4D& col) : m_TextureID(-1)
{ SetColor(col); }

RenderComponent::RenderComponent(float r, float g, float b) : m_TextureID(-1)
{ SetColor(Vec4(r, g, b,1.0f)); }

//Load Texture Manually
int RenderComponent::LoadTexture(const std::string& texturename)
{
  //Load Texture Function Here!
	return -1;
}

void RenderComponent::SetColor(float r, float g, float b,float a)
{
  SetColor(Vec4(r, g, b, a));
}

void RenderComponent::SetColor(const Vector4D& col)
{
	m_Color = col;
}

int RenderComponent::GetTextureID() const { return m_TextureID; }

Vector4D& RenderComponent::GetColor() { return m_Color; }

//-------------------------------------------------------------
//-------------------------------------------------------------
// TRANSFORM COMPONENT
//-------------------------------------------------------------
TransformComponent::TransformComponent() : m_scale(Vec2(1,1)){}

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

void TransformComponent::SetScale(float x, float y)
{
  m_scale.x = x; m_scale.y = y;
}

Vector3D TransformComponent::GetPosition(){ return m_position; }
Vector3D TransformComponent::GetRotation(){ return m_rotation; }
Vector2D TransformComponent::GetScale(){ return m_scale; }

//-------------------------------------------------------------