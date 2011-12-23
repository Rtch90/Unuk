#include "Game.h"

Game::Game(void) {
  _player = new Player(&_map);
  _npc = new NPC(&_map);

  _runGameReturnValue = gameMainMenu;
}

Game::~Game(void) {
  delete _player;
  delete _npc;
}

gameNavVal_t Game::Run(const string savegameIDArg) {
  _player->SetXY(50, 50);
  _player->LoadSprites("../Data/Media/Images/Characters/template.png", 40, 45);

  _npc->SetXY(300, 300);
  _npc->LoadSprites("../Data/Media/Images/Characters/template.png", 40,45);

  LoadSavegame(savegameIDArg);

  int fps;
  int frame;
  int nextGameTick = SDL_GetTicks();

  Timer frameTimer;
  frameTimer.Start();

  Timer fpsCalc;
  fpsCalc.Start();

  Timer renderTimer;
  Timer updateTimer;

  _gameRenderTime.SetXY(10, 10);
  _gameRenderTime.SetTextBlended("Render - XX", vsmall, COLOUR_BLACK);

  _gameUpdateTime.SetXY(10, 30);
  _gameUpdateTime.SetTextBlended("Update - XX", vsmall, COLOUR_BLACK);

  stringstream playerXYString;
  _playerXY.SetXY(10, 50);
  _playerXY.SetTextBlended("Player coords - XX XX", vsmall, COLOUR_BLACK);

  _gameRunning = true;
  while(_gameRunning) {
    updateTimer.Start();
    while((int)SDL_GetTicks() > nextGameTick) {
      HandleInput();
      UpdateGame();

      nextGameTick += SKIP_TICKS;
    }
    updateTimer.Pause();

    renderTimer.Start();
    Render();
    renderTimer.Pause();

    // Calculate and display our FPS.
    if(fpsCalc.GetTicks() >= 1000) {
      fps = frame / (fpsCalc.GetTicks() / 1000);

      stringstream caption;
      caption << "Unuk - FPS: " << fps;

      SDL_WM_SetCaption(caption.str().c_str(), NULL);

      fpsCalc.Start();
      frame = 0;

      // Check to see if we are allowed to display debug info.
      if(debugEnabled) {
        _gameUpdateTime.SetTextBlended("Update - " + updateTimer.GetTicksStr(), vsmall, COLOUR_BLACK);
        _gameRenderTime.SetTextBlended("Render - " + renderTimer.GetTicksStr(), vsmall, COLOUR_BLACK);

        playerXYString.str("");
        playerXYString << "Player coords: x" << _player->GetX() << ", y" << _player->GetY();
        _playerXY.SetTextBlended(playerXYString.str(), vsmall, COLOUR_BLACK);
      }
    }
    // Restrict the fps.
    if(1000 / MAX_FPS > frameTimer.GetTicks()) {
      // SDL_Delay does not accept a float so for higher framerate
      // limits there's an innacuracy. This is as much as 3fps
      // at a limit of 60fps.
      SDL_Delay((1000 / MAX_FPS) - frameTimer.GetTicks());
    }
    frameTimer.Start();
    frame++;
  }
  return _runGameReturnValue;
}

void Game::HandleInput(void) {
  if(_ingameMenu.GetStatus() == false) {
    while(SDL_PollEvent(&event)) {
      _player->HandleInput();

      if(event.key.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_ESCAPE)
          _ingameMenu.SetStatus(true);
        if(event.key.keysym.sym == SDLK_p)
          debugEnabled = !debugEnabled;
      }
      else if(event.type == SDL_QUIT) {
        _gameRunning = false;
        _runGameReturnValue = gameQuitGame;
        break;
      }
    }
  } else {
    switch(_ingameMenu.HandleInput()) {
    case ingameMenuNothing:
      break;
    case ingameMenuResume:
      _ingameMenu.SetStatus(false);
      break;
    case ingameMenuSaveGame:
      break;
    case ingameMenuLoadGame:
      break;
    case ingameMenuOptions:
      break;
    case ingameMenuMainMenu:
      _gameRunning = false;
      break;
    }

    if(event.type == SDL_QUIT) {
      _gameRunning = false;
      _ingameMenu.SetStatus(false);
      _runGameReturnValue = gameQuitGame;
    }
  }
}

void Game::UpdateGame(void) {
  if(_ingameMenu.GetStatus() == false) {
    _player->Update();
    _npc->Update();
  } else {
    // :D
  }
}

void Game::Render(void) {
  if(_ingameMenu.GetStatus() == false) {
    _map.Render();

    _player->Render();
    _npc->Render();

    if(debugEnabled) {
      _gameRenderTime.RenderLiteral();
      _gameUpdateTime.RenderLiteral();
      _playerXY.RenderLiteral();
    }
  } else {
    _ingameMenu.Render();
  }
  SDL_Flip(screen);
}

void Game::LoadSavegame(const string savegameIDArg) {
  _saveGameID = savegameIDArg;
  string saveFilename = "../Save/" + _saveGameID;

  // Converting to XML ftw!
  TiXmlDocument mapFile(saveFilename.c_str());
  assert(mapFile.LoadFile() == true);
  
  TiXmlElement* rootElem = NULL;
  TiXmlElement* dataElem = NULL;
  
  // <save> - Grab a save file.
  rootElem = mapFile.FirstChildElement("save");
  assert(rootElem != NULL);
  if(rootElem) {
    // <name> - Parse the player name.
    dataElem = rootElem->FirstChildElement("name");
    assert(dataElem != NULL);
    _player->SetName(dataElem->GetText());
    // </name>
    
    // <x> - Parse the player x coord.
    dataElem = dataElem->NextSiblingElement("x");
    assert(dataElem != NULL);
    int playerX = atoi(dataElem->GetText());
    // </x>
    
    // <y> - Parse the player y coord.
    dataElem = dataElem->NextSiblingElement("y");
    assert(dataElem != NULL);
    int playerY = atoi(dataElem->GetText());
    // </y>
    
    _player->SetXY(playerX, playerY);
    
    // <map> - Parse the map file.
    dataElem = dataElem->NextSiblingElement("map");
    assert(dataElem != NULL);
    _map.Load(dataElem->GetText());
    // </map>
  }
  // <save>
  
  // </save>
}

void Game::SaveSavegame(void) {
  string saveFilename = "../Save/" + _saveGameID;

  ofstream saveFile(saveFilename.c_str());
  assert(saveFile.is_open());

  // Write stuff.
}
