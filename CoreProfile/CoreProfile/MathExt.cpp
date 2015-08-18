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
  return Vector2D(lhs.x * rhs, lhs.y * rhs);
}

Vector2D operator*(float lhs, const Vector2D& rhs)
{
  return Vector2D(rhs.x * lhs, rhs.y * lhs);
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

Vector3D Vector3D::operator+(const Vector3D& rhs)
{
  return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3D Vector3D::operator-(const Vector3D& rhs)
{
  return Vector3D(x - rhs.x, y - rhs.y, x - rhs.z);
}

Vector3D Vector3D::operator/(float rhs)
{
  return Vector3D(x / rhs, y / rhs, z / rhs);
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs)
{
  x += rhs.x; y += rhs.y; z += rhs.z;
  return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs)
{
  x -= rhs.x; y -= rhs.y; z -= rhs.z;
  return *this;
}

Vector3D& Vector3D::operator/=(float rhs)
{
  x /= rhs; y /= rhs; z /= rhs;
  return *this;
}

Vector3D& Vector3D::operator*=(float rhs)
{
  x *= rhs; y *= rhs; z *= rhs;
  return *this;
}

Vector3D Vector3D::Normalize()
{
  float mag = Magnitude();
  return Vector3D(x / mag, y / mag, z / mag);
}

float Vector3D::Magnitude() const
{
  return sqrt(MagnitudeSq());
}

float Vector3D::MagnitudeSq() const
{
  return x*x + y*y + z*z;
}

//Returns the length of the projected vector
float Vector3D::Dot(const Vector3D& rhs) const
{
  return x*rhs.x + y*rhs.y + z*rhs.z;
}

Vector3D operator*(const Vector3D& lhs, float rhs)
{
  return Vector3D(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

Vector3D operator*(float lhs, const Vector3D& rhs)
{
  return Vector3D(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
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


Matrix4D::Matrix4D()
{
  //Creates an identity matrix
  for (int i = 0; i < 16; ++i) m[i] = 0;
  m00 = m11 = m22 = m33 = 1;
}

Matrix4D Matrix4D::SetTranslate(const Vector3D& rhs)
{
  return SetTranslate(rhs.x, rhs.y, rhs.z);
}

Matrix4D Matrix4D::SetTranslate(const Vector2D& rhs)
{
  return SetTranslate(rhs.x, rhs.y);
}

Matrix4D Matrix4D::SetTranslate(float x, float y, float z)
{
  Matrix4D temp;
  temp.m03 = x; temp.m13 = y; temp.m23 = z;
  return temp;
}

Matrix4D Matrix4D::SetScale(const Vector3D& rhs)
{
  return SetScale(rhs.x, rhs.y, rhs.z);
}

Matrix4D Matrix4D::SetScale(float x, float y, float z)
{
  Matrix4D temp;
  temp.m00 = x; temp.m11 = y; temp.m22 = z;
  return temp;
}

Matrix4D Matrix4D::SetScale(float rhs)
{
  return SetScale(rhs, rhs, rhs);
}

Matrix4D Matrix4D::operator*(const Matrix4D& rhs)
{
  Matrix4D temp;
  for (int x = 0; x < 16; ++x)
  {
    float sum = 0;
    for (int y = 0; y < 4; ++y)
      sum += m[x - (x % 4) + y] * rhs.m[x + (y * 4)];
    temp.m[x] = sum;
  }
  return temp;
}