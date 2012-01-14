#pragma once
#include <list>

class NPC;
class Character;

class WorldManager {
public:
  WorldManager(void);
  ~WorldManager(void);

  void Update(void);
  void Render(void);

  void AddNPC(NPC* npc);
  void RemoveNPC(int index);
  NPC* GetNPC(int index);

  int  GetNPCCount() { return _npcs.size(); }

  void OnPlayerAttack(Character* player);

private:
  std::list<NPC*> _npcs;
};
