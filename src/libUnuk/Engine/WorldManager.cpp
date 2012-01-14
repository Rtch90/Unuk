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

void WorldManager::OnPlayerAttack(Character* player) {
  int playerX = (int)(player->GetX() / 32.0f);
  int playerY = (int)(player->GetY() / 32.0f);
  int playerDir = player->GetDirectionFacing();

  std::list<NPC*>::iterator i = _npcs.begin();

  while(i != _npcs.end()) {
    NPC* npc = (*i);

    int npcX = (int)(npc->GetX() / 32.0f);
    int npcY = (int)(npc->GetY() / 32.0f);

    int diffX = npcX - playerX;
    int diffY = npcY - playerY;

    // Not in player's line of sight.
    if(diffX != 0 && diffY != 0) {
      ++i;
      continue;
    }

    // Distance is greater than 2.
    if(diffX > 2 || diffY > 2) {
      ++i;
      continue;
    }

    // Player not facing the npc.
    if((diffX < 0 && playerDir != Character::FACING_LEFT)   || 
       (diffX > 0 && playerDir != Character::FACING_RIGHT)  ||
       (diffY < 0 && playerDir != Character::FACING_UP)     ||
       (diffY > 0 && playerDir != Character::FACING_DOWN))
    {
      ++i;
      continue;
    }

    npc->SetHealth(npc->GetHealth() - 5);

    if(npc->GetHealth() <= 0) {
      i = _npcs.erase(i);
      delete npc;
    }
    else {
      ++i;
    }
  }
}
