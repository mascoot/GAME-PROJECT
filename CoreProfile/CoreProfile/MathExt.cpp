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

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
  return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
  return Vector2D(x - rhs.x, y - rhs.y);
}

Vector2D Vector2D::operator/(float rhs) const
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

Vector2D Vector2D::Normalize() const
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

//Default Constructor
Vector4D::Vector4D() : x(0), y(0), z(0), w(0) {}

//Conversion Constructor
Vector4D::Vector4D(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

//Copy Constructor
Vector4D::Vector4D(const Vector4D& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

Vector4D::Vector4D(const Vector3D& rhs, float W) : x(rhs.x), y(rhs.y), z(rhs.z), w(W){}

//Vector4D& Vector4D::operator= (const Vector4D& rhs)
//{
//  x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
//  return *this;
//}

Vector4D Vector4D::operator+(const Vector4D& rhs) const
{
  return Vector4D(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vector4D Vector4D::operator-(const Vector4D& rhs) const
{
  return Vector4D(x - rhs.x, y - rhs.y, x - rhs.z, w - rhs.w);
}

Vector4D Vector4D::operator/(float rhs) const
{
  return Vector4D(x / rhs, y / rhs, z / rhs, w / rhs);
}

Vector4D& Vector4D::operator+=(const Vector4D& rhs)
{
  x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
  return *this;
}

Vector4D& Vector4D::operator-=(const Vector4D& rhs)
{
  x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
  return *this;
}

Vector4D& Vector4D::operator/=(float rhs)
{
  x /= rhs; y /= rhs; z /= rhs; w /= rhs;
  return *this;
}

Vector4D& Vector4D::operator*=(float rhs)
{
  x *= rhs; y *= rhs; z *= rhs; w *= rhs;
  return *this;
}

Vector4D Vector4D::Normalize() const
{
  float mag = Magnitude();
  return Vector4D(x / mag, y / mag, z / mag, w / mag);
}

float Vector4D::Magnitude() const
{
  return sqrt(MagnitudeSq());
}

float Vector4D::MagnitudeSq() const
{
  return x*x + y*y + z*z + w*w;
}

//Returns the length of the projected vector
float Vector4D::Dot(const Vector4D& rhs) const
{
  return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
}

Vector4D operator*(const Vector4D& lhs, float rhs)
{
  return Vector4D(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
}

Vector4D operator*(float lhs, const Vector4D& rhs)
{
  return Vector4D(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs);
}

std::ostream& operator<<(std::ostream& os, const Vector4D& rhs)
{
  os << "< " << rhs.x << " : " << rhs.y << " : " << rhs.z << " : " << rhs.w << " >";
  return os;
}

Matrix4D::Matrix4D()
{
  //Creates an identity matrix
  for (int i = 0; i < 4; ++i)
    for (int y = 0; y < 4; ++y)
      m[i][y] = 0;
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
    int t = x % 4;
    for (int y = 0; y < 4; ++y)
    {
      sum += m[(int)(x*0.25f)][y] * rhs.m[y][t];
    }
    temp.m[t][x-(t*4)] = sum;
  }
  return temp;
}

Matrix4D& Matrix4D::operator=(const Matrix4D& rhs)
{
  for (int i = 0; i < 4; ++i)
    for (int y = 0; y < 4; ++y)
      m[i][y] = rhs.m[i][y];
  return *this;
}

//Matrix4D Matrix4D::Transpose()
//{
//  return Mat4D();
//}

Matrix4D Matrix4D::SetRotationX(float angle)
{
  // [1 0            0              0]
  // [0 cos(X Angle) - sin(X Angle) 0]
  // [0 sin(X Angle) cos(X Angle)   0]
  // [0 0            0              1]
  Matrix4D temp;
  temp.m11 = cos(angle);
  temp.m12 = -sin(angle);
  temp.m21 = sin(angle);
  temp.m22 = cos(angle);
  return temp;
}
Matrix4D Matrix4D::SetRotationY(float angle)
{
  //[cos(Y Angle)  0 sin(Y Angle) 0]
  //[0             1 0            0]
  //[-sin(Y Angle) 0 cos(Y Angle) 0]
  //[0             0 0            1]
  Matrix4D temp;
  temp.m00 = cos(angle);
  temp.m02 = sin(angle);
  temp.m20 = -sin(angle);
  temp.m22 = cos(angle);
  return temp;
}
Matrix4D Matrix4D::SetRotationZ(float angle)
{
  //[cos(Z Angle) - sin(Z Angle) 0 0]
  //[sin(Z Angle) cos(Z Angle)   0 0]
  //[0            0              1 0]
  //[0            0              0 1]
  Matrix4D temp;
  temp.m00 = cos(angle);
  temp.m01 = -sin(angle);
  temp.m10 = sin(angle);
  temp.m11 = cos(angle);
  return temp;
}