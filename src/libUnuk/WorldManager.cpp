#include "WorldManager.h"
#include "NPC.h"

WorldManager::WorldManager(void) {
}

WorldManager::~WorldManager(void) {
  for(std::list<NPC*>::iterator i = _npcs.begin(); i != _npcs.end(); ++i) {
    NPC* npc = (*i);
    delete npc;
  }
}

void WorldManager::Update(void) {
  for(std::list<NPC*>::iterator i = _npcs.begin(); i != _npcs.end(); ++i) {
    NPC* npc = (*i);
    npc->Update();
  }
}

void WorldManager::Render(void) {
  for(std::list<NPC*>::iterator i = _npcs.begin(); i != _npcs.end(); ++i) {
    NPC* npc = (*i);
    npc->Render();
  }
}

void WorldManager::AddNPC(NPC* npc) {
  _npcs.push_back(npc);
}

void WorldManager::RemoveNPC(int index) {
  int npcsIndex = 0;
  for(std::list<NPC*>::iterator i = _npcs.begin(); i != _npcs.end(); ++i) {
    NPC* npc = (*i);
    if(npcsIndex == index) {
      _npcs.erase(i);
      delete npc;
    }
    npcsIndex++;
  }
}

NPC* WorldManager::GetNPC(int index) {
  int npcsIndex = 0;
  for(std::list<NPC*>::iterator i = _npcs.begin(); i != _npcs.end(); ++i) {
    NPC* npc = (*i);
    if(npcsIndex == index) {
      return npc;
    }
    npcsIndex++;
  }
  return NULL;
}
