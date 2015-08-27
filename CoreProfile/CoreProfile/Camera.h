#ifndef CAMERA_H
#define CAMERA_H

#include "BaseComponents.h"
#include "MathExt.h"

class Camera
{
public:
  Camera();

  Matrix4D& GetPerspMatrix();
  Matrix4D& GetViewMatrix();

  void SetPosition(float, float, float);

  void SetPerspective(float fov, float aspect, float zNear, float zFar);
  void LookAt(const Vector3D&);

  void Move(const Vector3D&);

  void Shake(float);

  void Update();

private:
  bool _isDirty;
  float _sCounter;

  TransformComponent *transform;
  Vector3D _dir, _up;

  Matrix4D _pMatrix;
  Matrix4D _vMatrix;
};

#endif
