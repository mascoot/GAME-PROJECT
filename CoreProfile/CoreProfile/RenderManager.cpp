#include "RenderManager.h"

RenderManager::RenderManager()
{
  GLfloat quad[] = {
    -1.0f, -1.0f, 
    1.0f, -1.0f, 
    1.0f, 1.0f, 
    -1.0f, 1.0f,   };
  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

  indices = { 1, 2, 0, 3 };

  glGenBuffers(1, &indicesbuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

RenderManager::~RenderManager()
{

}

void RenderManager::Update()
{
	/*  Filling the triangles */
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*  Culling back-facing triangles for efficiency, but no back faces now */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/*  Enabling anti-aliasing */
	glEnable(GL_MULTISAMPLE);

  //for (auto elem : rComps)
  {
    //Vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
      0,                  // attribute
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
      GL_TRIANGLE_STRIP,      // mode
      indices.size(),    // count
      GL_UNSIGNED_INT,   // type
      (void*)0           // element array buffer offset
      );

    glDisableVertexAttribArray(0);
  }

  glDisable(GL_MULTISAMPLE);
  glDisable(GL_CULL_FACE);
}