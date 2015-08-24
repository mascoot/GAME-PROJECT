#ifndef CAMERA_H
#define CAMERA_H

#include "MathExt.h"

class cCamera
{
public:
  cCamera();

  Matrix4D& GetPerspMatrix();
  Matrix4D& GetViewMatrix();

  void SetPerspective(float fov, float aspect, float zNear, float zFar);
  void LookAt(const Vector3D&);

  void Move(const Vector3D&);

  void Shake(float);

  void Update();

private:
  bool _isDirty;
  float _sCounter;

  Vector3D _pos, _dir, _up;

  Matrix4D _pMatrix;
  Matrix4D _vMatrix;
};

#endif
