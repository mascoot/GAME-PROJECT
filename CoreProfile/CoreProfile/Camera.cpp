#include "Camera.h"

cCamera::cCamera(){}

Matrix4D& cCamera::GetPerspMatrix(){ return _pMatrix; }
Matrix4D& cCamera::GetViewMatrix(){ return _vMatrix; }

void cCamera::SetPerspective(float fov, float aspect, float zNear, float zFar)
{
  _pMatrix = GetPerspective(fov, aspect, zNear, zFar);
}

void cCamera::LookAt(const Vector3D& target)
{
  _dir = (Vector3D(target) - _pos).Normalize();
  //Vector3D right = _dir.Cross(_up);
  //_up = right.Cross(_dir);

  _vMatrix = GetLookAt(_pos, target, _up);
}