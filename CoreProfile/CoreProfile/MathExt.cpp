#include "MathExt.h"

//Default Constructor
Vector2D::Vector2D() : x(0), y(0){}

//Conversion Constructor
Vector2D::Vector2D(float X,float Y) : x(X), y(Y){}

//Copy Constructor
Vector2D::Vector2D(const Vector2D& rhs) : x(rhs.x), y(rhs.y){}

//Assignment Operator
Vector2D& Vector2D::operator=(const Vector2D& rhs)
{
  x = rhs.x; y = rhs.y;
  return *this;
}

Vector2D Vector2D::operator+(const Vector2D& rhs)
{
  return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D Vector2D::operator-(const Vector2D& rhs)
{
  return Vector2D(x - rhs.x, y - rhs.y);
}

Vector2D Vector2D::operator/(float rhs)
{
  return Vector2D(x / rhs, y / rhs);
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
  x += rhs.x; y += rhs.y;
  return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
  x -= rhs.x; y -= rhs.y;
  return *this;
}

Vector2D& Vector2D::operator/=(float rhs)
{
  x /= rhs; y /= rhs;
  return *this;
}

Vector2D& Vector2D::operator*=(float rhs)
{
  x *= rhs; y *= rhs;
  return *this;
}

Vector2D Vector2D::Normalize()
{
  float mag = Magnitude();
  return Vector2D(x / mag, y / mag);
}


float Vector2D::Magnitude() const
{
  return sqrt(MagnitudeSq());
}

float Vector2D::MagnitudeSq() const
{
  return x*x + y*y;
}

//Returns the length of the projected vector
float Vector2D::Dot(const Vector2D& rhs) const
{
  return x*rhs.x + y*rhs.y;
}

float Vector2D::GetAngle(const Vector2D& rhs) const
{
  return this->Dot(rhs) / acos(this->Magnitude() * rhs.Magnitude());
}

Vector2D operator*(const Vector2D& lhs, float rhs)
{
  return Vector2D(lhs.x / rhs, lhs.y / rhs);
}

Vector2D operator*(float lhs, const Vector2D& rhs)
{
  return Vector2D(rhs.x / lhs, rhs.y / lhs);
}

std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
{
  os << "< " << rhs.x << " : " << rhs.y << " >";
  return os;
}

//Default Constructor
Vector3D::Vector3D() : x(0), y(0), z(0){}

//Conversion Constructor
Vector3D::Vector3D(float X, float Y, float Z) : x(X), y(Y), z(Z){}

//Copy Constructor
Vector3D::Vector3D(const Vector3D& rhs) : x(rhs.x), y(rhs.y), z(rhs.z){}

Vector3D::Vector3D(const Vector2D& rhs, float depth) : x(rhs.x), y(rhs.y), z(depth){}

Vector3D& Vector3D::operator = (const Vector3D& rhs)
{
  x = rhs.x; y = rhs.y; z = rhs.z;
  return *this;
}

Vector3D Vector3D::Cross(const Vector3D& r)
{
  return Vector3D(y*r.z - z*r.y, z*r.x - x*r.z, x*r.y - y*r.x);
}

std::ostream& operator<<(std::ostream& os, const Vector3D& rhs)
{
  os << "< " << rhs.x << " : " << rhs.y << " : " << rhs.z << " >";
  return os;
}