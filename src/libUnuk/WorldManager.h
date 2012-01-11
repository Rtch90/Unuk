#pragma once
#include <list>

class NPC;

class WorldManager {
public:
  WorldManager(void);
  ~WorldManager(void);

  void Update(void);
  void Render(void);

  void AddNPC(NPC* npc);
  void RemoveNPC(int index);
  NPC* GetNPC(int index);

private:
  std::list<NPC*> _npcs;
};
