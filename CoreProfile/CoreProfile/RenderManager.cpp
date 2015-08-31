#include "RenderManager.h"

RenderManager::RenderManager()
{
  GLfloat quad[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f  };

  GLfloat uv[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f };

  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

  glGenBuffers(1, &uvbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

  indices = { 1, 2, 0, 3 };

  glGenBuffers(1, &indicesbuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  LoadShaders();
}

void RenderManager::LoadShaders()
{
  cam.SetPerspective(DEG2RAD(60.0f), 1280.0f / 720.0f, 0.001f, 10000.0f);

  std::vector<Shader> shaders;
  shaders.reserve(2);
  shaders.push_back(Shader::LoadShader("./shaders/shader.vs", GL_VERTEX_SHADER));
  shaders.push_back(Shader::LoadShader("./shaders/shader.fs", GL_FRAGMENT_SHADER));
  gProgram = new ShaderProgram(shaders);

  gProgram->BindShader();

  //Constant Matrix unless there is a change in camera FOV
  gProgram->SetUniform("projection", cam.GetPerspMatrix());
  
  gProgram->UnbindShader();
}

RenderManager::~RenderManager()
{
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteBuffers(1, &uvbuffer);
  glDeleteBuffers(1, &indicesbuffer);
}

void RenderManager::Update()
{
	/*  Filling the triangles */
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*  Culling back-facing triangles for efficiency, but no back faces now */
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	/*  Enabling anti-aliasing */
	glEnable(GL_MULTISAMPLE);

  static float angle = 0;
  
  //This just rotates the camera around the origin
  cam.SetPosition(sin(angle) * 5, 0, cos(angle) * 5);
  cam.LookAt(Vec3(0, 0, 0));
  
  angle += 0.01f;

  for (auto elem : rComps)
  {
    gProgram->BindShader();

    gProgram->SetUniform("camera", cam.GetViewMatrix());

    Mat4D modelMat;

    gProgram->SetUniform("model", modelMat);
    gProgram->SetUniform("my4Color",Vec4(1, 1, 0, 1));

    //Enable Vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
      0,                  // attribute
      3,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
      );

    //Enable UV
    //glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
      1,                  // attribute
      2,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
      );

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);

    // Draw the triangles !
    glDrawElements(
      GL_TRIANGLE_STRIP, // mode
      indices.size(),    // count
      GL_UNSIGNED_INT,   // type
      (void*)0           // element array buffer offset
      );

    glDisableVertexAttribArray(1); // Disable UV
    glDisableVertexAttribArray(0); // Diable Vertices

    gProgram->UnbindShader();
  }

  glDisable(GL_MULTISAMPLE);
  glDisable(GL_CULL_FACE);
}