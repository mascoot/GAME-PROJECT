#include "GameObject.h"

TestObject::TestObject() : transform(new TransformComponent()),
renderer(new RenderComponent())
{
  transform->SetSize(2, 1);
}

void TestObject::Update()
{

}
