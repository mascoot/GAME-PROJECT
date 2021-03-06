#ifndef MATH_EXT_H
#define MATH_EXT_H

#include <iostream>
#include <math.h>

#define DEG2RAD(x) x*0.0174532925f

typedef union Vector2D
{
  struct
  {
    float x, y;
  };

  float m[2];

  Vector2D();
  Vector2D(float, float);
  Vector2D(const Vector2D&);

  Vector2D& operator=(const Vector2D&);

  Vector2D operator+(const Vector2D&) const;
  Vector2D operator-(const Vector2D&) const;
  Vector2D operator/(float) const;
  
  Vector2D& operator+=(const Vector2D&);
  Vector2D& operator-=(const Vector2D&);
  Vector2D& operator/=(float);
  Vector2D& operator*=(float);

  Vector2D Normalize() const;
  
  float Magnitude() const;
  float MagnitudeSq() const; 
  float Dot(const Vector2D&) const;
  float GetAngle(const Vector2D&) const;
} Vec2;

Vector2D operator*(const Vector2D&, float);
Vector2D operator*(float,const Vector2D&);

std::ostream& operator<<(std::ostream&, const Vector2D&);


typedef union Vector3D
{
  struct
  {
    float x, y, z;
  };

  float m[3];

  Vector3D();
  Vector3D(float, float, float);
  Vector3D(const Vector3D&);
  Vector3D(const Vector2D&, float = 0.0f);

  Vector3D& operator=(const Vector3D&);

  Vector3D operator+(const Vector3D&);
  Vector3D operator-(const Vector3D&);
  Vector3D operator/(float);

  Vector3D& operator+=(const Vector3D&);
  Vector3D& operator-=(const Vector3D&);
  Vector3D& operator/=(float);
  Vector3D& operator*=(float);

  Vector3D Normalize();

  float Magnitude() const;
  float MagnitudeSq() const;
  float Dot(const Vector3D&) const;

  Vector3D Cross(const Vector3D&);
} Vec3;

Vector3D operator*(const Vector3D&, float);
Vector3D operator*(float, const Vector3D&);

std::ostream& operator<<(std::ostream&, const Vector3D&);

typedef union Vector4D
{
  struct
  {
    float x, y, z, w;
  };

  float m[4];

  Vector4D();
  Vector4D(float, float, float, float);
  Vector4D(const Vector4D&);
  Vector4D(const Vector3D&, float = 0.0f);

  //Vector4D& operator=(const Vector4D&);

  Vector4D operator+(const Vector4D&) const;
  Vector4D operator-(const Vector4D&) const;
  Vector4D operator/(float) const;

  Vector4D& operator+=(const Vector4D&);
  Vector4D& operator-=(const Vector4D&);
  Vector4D& operator/=(float);
  Vector4D& operator*=(float);

  Vector4D Normalize() const;

  float Magnitude() const;
  float MagnitudeSq() const;
  float Dot(const Vector4D&) const;

} Vec4;

Vector4D operator*(const Vector4D&, float);
Vector4D operator*(float, const Vector4D&);

std::ostream& operator<<(std::ostream&, const Vector4D&);

//Note* Matrix class is Row Major, however OpenGL Matrix is Col Major thus
// Matrix4D = Transpose of OpenGL Matrix
typedef union Matrix4D
{
  struct
  {
    float
      m00, m01, m02, m03,
      m10, m11, m12, m13,
      m20, m21, m22, m23,
      m30, m31, m32, m33;
  };

  float m[4][4];

  Matrix4D();

  Matrix4D SetTranslate(const Vector3D&);
  Matrix4D SetTranslate(const Vector2D&);
  Matrix4D SetTranslate(float, float, float = 0.0f);
  
  Matrix4D SetScale(const Vector3D&);
  Matrix4D SetScale(float, float, float);
  Matrix4D SetScale(float);

  Matrix4D SetRotationX(float);
  Matrix4D SetRotationY(float);
  Matrix4D SetRotationZ(float);

  Matrix4D operator*(const Matrix4D&);
  Matrix4D& operator=(const Matrix4D&);
  //Matrix4D Transpose();

  //float* operator[](unsigned index);

  //static Matrix4D Ortho(float left, float right, float up, float down, float near, float far);
  //static Matrix4D Ortho(float left, float right, float up, float down);

} Mat4D;

#endif
