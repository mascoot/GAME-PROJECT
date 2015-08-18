#include "Shader.h"
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& file, GLenum type) : _object(0), _refCount(nullptr)
{
  _object = glCreateShader(type);

  if (_object == 0)
    throw std::runtime_error("glCreateShader failed");

  //set the source code
  const char* code = file.c_str();
  glShaderSource(_object, 1, (const GLchar**)&code, nullptr);

  glCompileShader(_object);

  //throw exception if compile error occurred
  GLint status;
  glGetShaderiv(_object, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) 
  {
    glDeleteShader(_object); _object = 0;
    throw std::runtime_error("Compile failure in shader");
  }

  _refCount = new unsigned;
  *_refCount = 1;
}

Shader::Shader(const Shader& rhs) : _object(rhs._object), _refCount(rhs._refCount)
{
  _retain();
}

Shader& Shader::operator= (const Shader& rhs) 
{
  _release();
  _object = rhs._object;
  _refCount = rhs._refCount;
  _retain();
  return *this;
}

Shader::~Shader()
{
  if (_refCount) _release();
}

void Shader::_retain() 
{
  *_refCount += 1;
}

void Shader::_release() 
{
  *_refCount -= 1;
  if (*_refCount == 0)
  {
    glDeleteShader(_object); _object = 0;
    delete _refCount; _refCount = NULL;
  }
}

GLuint Shader::Object() const { return _object; }

Shader Shader::LoadShader(const std::string& file, GLenum type)
{
  std::ifstream f;
  f.open(file.c_str(), std::ios::in | std::ios::binary);
  if (!f.is_open()){
    throw std::runtime_error(std::string("Failed to open file: ") + file);
  }

  //read whole file into stringstream buffer
  std::stringstream buffer;
  buffer << f.rdbuf();

  Shader temp(buffer.str(), type);
  return temp;
}

//-------------------------------------------------------------------------
//---------------- SHADER PROGRAM CLASS -----------------------------------
//-------------------------------------------------------------------------

ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders) : _object(0)
{
  if (shaders.size() <= 0) 
    throw std::runtime_error("No shaders were provided to create the program");

  _object = glCreateProgram();
  if (_object == 0)
    throw std::runtime_error("glCreateProgram failed");

  //attach all shaders 
  for (unsigned i = 0; i < shaders.size(); ++i)
    glAttachShader(_object, shaders[i].Object());

  //Link all shaders together
  glLinkProgram(_object);

  //detach all shaders
  for (unsigned i = 0; i < shaders.size(); ++i)
    glDetachShader(_object, shaders[i].Object());

  //throw exception if linking failed
  GLint status;
  glGetProgramiv(_object, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) 
  {
    glDeleteProgram(_object); _object = 0;
    throw std::runtime_error("Shader Program linking failed");
  }
}

ShaderProgram::~ShaderProgram() 
{
  if (_object != 0) glDeleteProgram(_object);
}

GLuint ShaderProgram::Object() const { return _object; }

GLint ShaderProgram::GetAttribute(const GLchar* name) const
{
  if (!name)
    throw std::runtime_error("attribName was NULL");

  GLint attrib = glGetAttribLocation(_object, name);
  if (attrib == -1)
    throw std::runtime_error(std::string("Program attribute not found: ") + name);

  return attrib;
}

GLint ShaderProgram::GetUniform(const GLchar* name) const
{
  if (!name)
    throw std::runtime_error("uniformName was NULL");

  GLint uniform = glGetUniformLocation(_object, name);
  if (uniform == -1)
    throw std::runtime_error(std::string("Program uniform not found: ") + name);

  return uniform;
}

void ShaderProgram::BindShader() const {
  glUseProgram(_object);
}

void ShaderProgram::UnbindShader() const
{
  glUseProgram(0);
}

bool ShaderProgram::InUse() const {
  GLint currentProgram = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
  return (currentProgram == (GLint)_object);
}

