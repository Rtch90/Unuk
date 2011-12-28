#ifndef _GAME_H_
#define _GAME_H_
#include <SDL/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <tinyxml.h>

#include "Constants.h"
#include "Globals.h"
#include "Player.h"
#include "../libUnuk/IngameMenu.h"
#include "../libUnuk/Map.h"
#include "../libUnuk/Timer.h"
#include "../libUnuk/NPC.h"
#include "../libUnuk/Debug.h"
#include "../libUnuk/Text.h"
using namespace std;

enum gameNavVal_t { gameMainMenu, gameQuitGame };

class Game {
public:
  Game(void);
  ~Game(void);

  gameNavVal_t Run(const string savegameIDArg);

private:
  void HandleInput(void);
  void UpdateGame(void);
  void Render(void);

  void LoadSavegame(const string savegameIDArg);
  void SaveSavegame(void);

  static const int MAX_FPS = 200;
  static const int GAME_UPDATES_PER_SECOND = 60;
  static const int SKIP_TICKS = 1000 / GAME_UPDATES_PER_SECOND;

  bool _gameRunning;

  gameNavVal_t _runGameReturnValue;

  string _saveGameID;
  string _mapID;

  Text _gameUpdateTime;
  Text _gameRenderTime;
  Text _playerXY;
  Text _playerHealth;
  Text _npcHealth;

  IngameMenu _ingameMenu;
  Map _map;

  Player* _player;
  NPC* _npc;
};

#endif
