#ifndef _GAME_H_
#define _GAME_H_
#include <SDL/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

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

const int GAME_RETURN_TO_MMENU  = 0;
const int GAME_QUIT_GAME        = 1;

class Game {
public:
  Game(void);
  ~Game(void);

  int Run(const string savegameIDArg);

private:
  void HandleInput(void);
  void UpdateGame(void);
  void Render(void);

  void LoadSavegame(const string savegameIDArg);
  void SaveSavegame(void);

  bool m_gameRunning;

  int m_runGameReturnValue;

  string m_saveGameID;
  string m_mapID;

  Text m_gameUpdateTime;
  Text m_gameRenderTime;
  Text m_playerXY;

  static const int MAX_FPS = 6000;
  static const int GAME_UPDATES_PER_SECOND = 60;
  static const int SKIP_TICKS = 1000 / GAME_UPDATES_PER_SECOND;

  IngameMenu* m_ingameMenu;
  Map* m_map;

  Player* m_player;
  NPC* m_npc;
};

#endif
