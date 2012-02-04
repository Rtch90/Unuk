#pragma once
#include <list>

class NPC;
class Player;
class LevelGen;

class WorldManager {
public:
  WorldManager(LevelGen* level);
  ~WorldManager(void);

  void Update(void);
  void Render(void);

  void AddNPC(NPC* npc);
  void RemoveNPC(int index);
  NPC* GetNPC(int index);
  NPC* GetNPCAt(int xArg, int yArg);
  void CreateNPC(int x, int y);
  

  int  GetNPCCount() { return _npcs.size(); }

  void OnPlayerAttack(Player* player);

private:
  LevelGen* _level;
  std::list<NPC*> _npcs;
};
