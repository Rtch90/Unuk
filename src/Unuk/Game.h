#pragma once
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
#include "../libUnuk/UI/IngameMenu.h"
#include "../libUnuk/LevelGen/LevelGen.h"
#include "../libUnuk/System/Timer.h"
#include "../libUnuk/System/Debug.h"
#include "../libUnuk/UI/Text.h"
#include "../libUnuk/UI/Bar.h"
#include "../libUnuk/UI/EventHistory.h"
#include "../libUnuk/Engine/MemClass.h"
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
  Text _npcHealth;

  IngameMenu _ingameMenu;
	LevelGen _map;

  Player* _player;

  Text  _playerHealth;
  Bar   _playerHealthBar;

  EventHistory _eventHistory;
};
