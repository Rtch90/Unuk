#include "WorldManager.h"
#include "NPC.h"
#include "../../Unuk/Player.h"
#include "../../Unuk/Globals.h"
#include "../UI/EventHistory.h"

WorldManager::WorldManager(LevelGen* level) {
	_level = level;
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

NPC* WorldManager::GetNPCAt(int xArg, int yArg) {
	for(std::list<NPC*>::iterator i = _npcs.begin(); i != _npcs.end(); ++i) {
		NPC* npc = (*i);
		if(xArg >= npc->GetX() && xArg <= (npc->GetX() + npc->GetWidth()) &&
			 yArg >= npc->GetY() && yArg <= (npc->GetY() + npc->GetHeight())) {
			return npc;
		}
	}
	return NULL;
}

void WorldManager::CreateNPC(int x, int y) {
	NPC* npc = new NPC(_level);
	npc->SetXY(x, y);
	npc->LoadSprites("../Data/Media/Images/Characters/template.png", 40,45);
	_npcs.push_back(npc);
}

bool WorldManager::CheckCollision(const SDL_Rect& charRect, Character* exclude) {
	for(std::list<NPC*>::iterator i = _npcs.begin(); i != _npcs.end(); ++i) {
		NPC* npc = (*i);

		if(npc == exclude) {
			continue;
		}

		SDL_Rect npcRect;
		npcRect.x = npc->GetX();
		npcRect.y = npc->GetY();
		npcRect.w = npc->GetWidth();
		npcRect.h = npc->GetHeight();

		if(CheckCollisionRect(npcRect, charRect)) {
			return true;
		}
	}
	return false;
}

void WorldManager::OnPlayerAttack(Player* player) {
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
		if(abs(diffX) > 2 || abs(diffY) > 2) {
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

		npc->SetHealth(npc->GetHealth() - 20);
		npc->OnAttack();

		if(npc->GetHealth() <= 0) {

			// Please note:
			// Naked dudes are known to be sensitive to spicy food.

			std::string waysOfDeath[] = {
				"Choked Naked Dude!",
				"Stabbed Naked Dude!",
				"Urinated Acid on Naked Dude!",
				"Killed Naked Dude with a dildo!",
				"Poured Tabasco on Naked Dude!",
				"Threw Acid on Naked Dude!",
				"Slapped Naked Dude with Dead Fish!",
				"Killed Naked Dude with a Pistol!",
				"Ate Naked Dude's brain!",
				"Slaughtered Naked Dude!",
				"Roasted Naked Dude!",
				"Pepper Sprayed Naked Dude!",
				"Stoned Naked Dude!",
				"Slayed Naked Dude with a Katana!",
				"Threw Chili Peppers on Naked Dude!",
				"Used Karate on Naked Dude!",
				"Beat the shit out of Naked Dude!",
				"FUS RO DAH!"
			};

			eventHistory->LogEvent(waysOfDeath[rand() % (sizeof(waysOfDeath)/sizeof(std::string))]);

			int expGain = 3 + (rand() % 2);
			player->SetExp(player->GetExp() + expGain);

			i = _npcs.erase(i);
			delete npc;

			if(_npcs.empty()) {
				_level->New();

				int spawnX;
				int spawnY;
				_level->FindSpawnPoint(spawnX, spawnY, player->GetWidth(),player->GetHeight());
				player->SetXY(spawnX, spawnY);
			}
		}
		else {
			++i;
		}
	}
}

void WorldManager::OnPlayerMove(Player* player) {
	for(std::list<NPC*>::iterator i = _npcs.begin(); i != _npcs.end(); ++i) {
		(*i)->OnPlayerMove(player);
	}
}
