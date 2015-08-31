#include "GameObject.h"

BaseObject::BaseObject()
{
  tID = ICompManager::Inst()->AddTransfCmp();
  ICompManager::Inst()->GetTransfCmp(tID).SetScale(2, 1);

  rID = ICompManager::Inst()->AddRenderCmp();
  ICompManager::Inst()->GetRenderCmp(rID).SetColor(1,0.4,0,0.5);
}

void BaseObject::Update()
{

}
