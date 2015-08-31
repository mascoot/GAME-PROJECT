#ifndef BASE_COMP_H
#define BASE_COMP_H

#include <vector>
#include <list>
#include <algorithm>
#include "MathExt.h"

class TransformComponent;
class RenderComponent;
class ShaderComponent;

class ICompManager
{
public:
  static ICompManager* Inst();

  void AddTransfCmp(TransformComponent*);
  void AddRenderCmp(RenderComponent*);
  void AddShaderCmp(ShaderComponent*);

private:
  static ICompManager* m_inst;

  std::list<TransformComponent*> tComps;
  std::list<RenderComponent*> rComps;
  std::list<ShaderComponent*> sComps;
};

class IComponent
{
public:
	unsigned GetID() const;
	IComponent();
private:
	static unsigned m_Counter;
	unsigned m_ID;

};

class RenderComponent : public IComponent
{
public:
	//Initialize Component with Texture
	RenderComponent(const std::string&);
	//Initialize Component with Color
	RenderComponent();
	RenderComponent(const Vector3D&);
	RenderComponent(float, float, float);

	//Load Texture Manually
	int LoadTexture(const std::string&);
	//Set Color Override Manually
	void SetColor(const Vector3D&);

	int GetTextureID() const;
	Vector3D& GetColor();

private:
	int m_TextureID;
	Vector3D m_Color;
};

class ShaderComponent : public IComponent
{
  int GetShaderID();
  bool LoadShader(const std::string&);

private:
  int m_shaderID;
  
};

class TransformComponent : public IComponent
{
public:
  TransformComponent();

  void SetPosition(const Vector3D&);
  void SetPosition(float, float, float);
  void SetRotation(const Vector3D&);
  void SetRotation(float, float, float);
  void SetSize(float, float);

  Vector3D GetPosition();
  Vector3D GetRotation();
  Vector2D GetScale();

private:
	Vec3 m_position;
  Vec3 m_rotation;
  Vec2 m_scale;

};

#endif