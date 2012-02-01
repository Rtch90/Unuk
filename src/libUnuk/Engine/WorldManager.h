#pragma once
#include <list>

class NPC;
class Player;

class WorldManager {
public:
  WorldManager(void);
  ~WorldManager(void);

  void Update(void);
  void Render(void);

  void AddNPC(NPC* npc);
  void RemoveNPC(int index);
  NPC* GetNPC(int index);
  
  bool HasNPCIn(int xArg, int yArg);

  int  GetNPCCount() { return _npcs.size(); }

  void OnPlayerAttack(Player* player);

private:
  std::list<NPC*> _npcs;
};
