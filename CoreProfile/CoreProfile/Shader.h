#include "gl/gl3w.h"
#include <string>
#include <vector>

class Shader
{
public:
  Shader(const std::string&, GLenum);
  Shader(const Shader&);

  ~Shader();

  static Shader LoadShader(const std::string&, GLenum);

  GLuint Object() const;

  Shader& operator= (const Shader&);

private:
  GLuint _object;
  unsigned* _refCount;

  void _retain();
  void _release();
};

class ShaderProgram
{
public:
  ShaderProgram(const std::vector<Shader>&);
  ~ShaderProgram();

  GLuint Object() const;

  GLint GetAttribute(const GLchar*) const;
  GLint GetUniform(const GLchar*) const;

  void BindShader() const;
  void UnbindShader() const;

private:
  GLuint _object;

  bool InUse() const;

};