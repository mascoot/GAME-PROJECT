#include "Camera.h"

Camera::Camera() : transform(new TransformComponent()) 
{
  _dir = Vec3();
  _up = Vec3(0, 1, 0);
}

Matrix4D& Camera::GetPerspMatrix(){ return _pMatrix; }
Matrix4D& Camera::GetViewMatrix(){ return _vMatrix; }

void Camera::SetPosition(float x, float y, float z)
{
  transform->position = Vec3(x, y, z);
}

void Camera::SetPerspective(float fov, float aspect, float zNear, float zFar)
{
  float tanHalfVerticalFov = tan(fov * 0.5f);

  _pMatrix.m[0][0] = 1.0f / (aspect * tanHalfVerticalFov);
  _pMatrix.m[1][1] = 1.0f / (tanHalfVerticalFov);
  _pMatrix.m[2][2] = -(zFar + zNear) / (zNear - zFar);
  _pMatrix.m[2][3] = -1.0f;
  _pMatrix.m[3][3] = -(2.0f * zFar * zNear) / (zNear - zFar);
}

void Camera::LookAt(const Vector3D& target)
{
  _dir = (Vector3D(target) - transform->position).Normalize();
  Vector3D right((_dir.Cross(_up)).Normalize());
  _up = (right.Cross(_dir));

  _vMatrix.m00 = right.x;
  _vMatrix.m10 = right.y;
  _vMatrix.m20 = right.z;
  _vMatrix.m01 = _up.x;
  _vMatrix.m11 = _up.y;
  _vMatrix.m21 = _up.z;
  _vMatrix.m02 = -_dir.x;
  _vMatrix.m12 = -_dir.y;
  _vMatrix.m22 = -_dir.z;
  _vMatrix.m30 = -right.Dot(transform->position);
  _vMatrix.m31 = -_up.Dot(transform->position);
  _vMatrix.m32 = _dir.Dot(transform->position);
}