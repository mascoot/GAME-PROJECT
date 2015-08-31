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

  unsigned AddTransfCmp();
  unsigned AddRenderCmp();
  unsigned AddShaderCmp();

  TransformComponent& GetTransfCmp(unsigned);
  RenderComponent& GetRenderCmp(unsigned);
  ShaderComponent& GetShaderCmp(unsigned);

  std::vector<TransformComponent>* GetTransformList()
  { return &tComps; }

  std::vector<RenderComponent>* GetRenderList()
  { return &rComps; }

  std::vector<ShaderComponent>* GetShaderList()
  { return &sComps; }

private:
  static ICompManager* m_inst;

  std::vector<TransformComponent> tComps;
  std::vector<RenderComponent> rComps;
  std::vector<ShaderComponent> sComps;
};

#define iTRANSFORM(x) ICompManager::Inst()->GetTransfCmp(x)
#define iRENDER(x) ICompManager::Inst()->GetRenderCmp(x)
#define iSHADER(x) ICompManager::Inst()->GetShaderCmp(x)

class IComponent
{
public:
  void SetID(unsigned);
	unsigned GetID() const;
  void SetActive(bool);
  bool IsActive() const;
	IComponent();
private:
	unsigned m_ID;
  bool m_isActive;
};

class RenderComponent : public IComponent
{
public:
	//Initialize Component with Texture
	RenderComponent(const std::string&);
	//Initialize Component with Color
	RenderComponent();
	RenderComponent(const Vector4D&);
	RenderComponent(float, float, float);

	//Load Texture Manually
	int LoadTexture(const std::string&);
	//Set Color Override Manually
  void SetColor(float, float, float,float);
	void SetColor(const Vector4D&);

	int GetTextureID() const;
	Vector4D& GetColor();

private:
	int m_TextureID;
	Vector4D m_Color;
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
  void SetScale(float, float);

  Vector3D GetPosition();
  Vector3D GetRotation();
  Vector2D GetScale();

private:
	Vec3 m_position;
  Vec3 m_rotation;
  Vec2 m_scale;

};

#endif