#ifndef MATH_EXT_H
#define MATH_EXT_H

#include <iostream>
#include <math.h>

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

  Vector2D operator+(const Vector2D&);
  Vector2D operator-(const Vector2D&);
  Vector2D operator/(float);
  
  Vector2D& operator+=(const Vector2D&);
  Vector2D& operator-=(const Vector2D&);
  Vector2D& operator/=(float);
  Vector2D& operator*=(float);

  Vector2D Normalize();
  
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

#endif