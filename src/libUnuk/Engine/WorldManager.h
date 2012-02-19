#pragma once
#include <list>
#include "MemClass.h"

class Character;
class NPC;
class Player;
class LevelGen;

#include <SDL/SDL.h>

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

	bool CheckCollision(const SDL_Rect& charRect, Character* exclude);

	int  GetNPCCount() { return _npcs.size(); }

	void OnPlayerAttack(Player* player);
	void OnPlayerMove(Player* player);

	// Overload new and delete operators to utilize MemManager.
	inline void* operator new(size_t size) {
		return gMemManager.Allocate(size);
	}

	inline void operator delete(void* object) {
		gMemManager.Free(object);
	}

	inline void* operator new [](size_t size) {
		return gMemManager.Allocate(size);
	}

	inline void operator delete [](void* object) {
		gMemManager.Free(object);
	}

private:
	LevelGen* _level;
	std::list<NPC*> _npcs;
};
