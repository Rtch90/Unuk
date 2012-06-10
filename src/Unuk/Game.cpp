#include "Game.h"
#include "../libUnuk/Engine/MemManager.h"
#include "../libUnuk/Engine/NPC.h"
#include "../libUnuk/Engine/WorldManager.h"
#include "../Unuk/Globals.h"
#include "../libUnuk/UI/EventHistory.h"

Game::Game(void) {
  Debug::logger->message("Creating characters..");
  _player = scNew(Player,(&_map));
  _map.SetPlayer(_player);

  _runGameReturnValue = gameMainMenu;
}

Game::~Game(void) {
  Debug::logger->message("\n----- Cleaning Up ------");
  // cleaning _player up caused a nice seg fault. I'll look later.
  //delete _player;
}

void Game::New(const string& savegameIDArg) {
  _saveGameID = savegameIDArg;
  NewSavegame(savegameIDArg);

  int spawnX;
  int spawnY;
  _map.FindSpawnPoint(spawnX, spawnY, 40, 45);

  _player->SetXY((float)spawnX, (float)spawnY);
}

void Game::Load(const string& savegameIDArg) {
  _saveGameID = savegameIDArg;
  LoadSavegame(savegameIDArg);

  int spawnX;
  int spawnY;
  _map.FindSpawnPoint(spawnX, spawnY, 40, 45);

  _player->SetXY((float)spawnX, (float)spawnY);
}

gameNavVal_t Game::Run(void) {
  _player->LoadSprites("../Data/Media/Images/Characters/Reniesta.png", 40, 45);

  int fps = 0;
  int frame = 0;
  int nextGameTick = SDL_GetTicks();

  Timer frameTimer;
  frameTimer.Start();

  Timer fpsCalc;
  fpsCalc.Start();

  Timer renderTimer;
  Timer updateTimer;

  stringstream playerHealth;
  _playerHealth.SetXY(15, 27);
  _playerHealth.SetTextBlended("Player Health - XX", vsmall, COLOUR_WHITE);

  stringstream playerExp;
  _playerExp.SetXY(15, 57);
  _playerExp.SetTextBlended("Player Level XX (XX/XX)", vsmall, COLOUR_WHITE);

  _gameRenderTime.SetXY(10, 90);
  _gameRenderTime.SetTextBlended("Render - XX", vsmall, COLOUR_BLACK);

  _gameUpdateTime.SetXY(10, 110);
  _gameUpdateTime.SetTextBlended("Update - XX", vsmall, COLOUR_BLACK);

  stringstream playerXYString;
  _playerXY.SetXY(10, 130);
  _playerXY.SetTextBlended("Player coords - XX XX", vsmall, COLOUR_BLACK);

  _playerHealthBar.SetBackgroundRGB(0, 0, 0);
  _playerHealthBar.SetForegroundRGB(255, 0, 0);
  _playerHealthBar.SetXY(10, 20);
  _playerHealthBar.SetWidthHeight(200, 25);

  _playerExpBar.SetBackgroundRGB(0, 0, 0);
  _playerExpBar.SetForegroundRGB(0, 0, 255);
  _playerExpBar.SetXY(10, 50);
  _playerExpBar.SetWidthHeight(200, 25);
  _playerExpBar.SetProgress(0.0f);

  eventHistory = scNew(EventHistory,);

  _gameRunning = true;
  while(_gameRunning) {
    bool stillRunning = true;

    updateTimer.Start();
    while((int)SDL_GetTicks() > nextGameTick) {
      HandleInput();
      if (!_gameRunning) {
        stillRunning = false;
        break;
      }

      UpdateGame();

      nextGameTick += SKIP_TICKS;
    }
    updateTimer.Pause();

    if (!stillRunning) {
      break;
    }

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

      playerHealth.str("");
      playerHealth << "Player Health - " << _player->GetHealth();
      _playerHealth.SetTextBlended(playerHealth.str(), vsmall, COLOUR_WHITE);

      _playerHealthBar.SetProgress((float)_player->GetHealth() / 100.0f);

      playerExp.str("");
      playerExp << "Player Level " << _player->GetLevel() <<  "  (" << _player->GetExp() << "/" << Player::EXP_TABLE[_player->GetLevel() - 1] << ")";
      _playerExp.SetTextBlended(playerExp.str(), vsmall, COLOUR_WHITE);

      _playerExpBar.SetProgress((float)_player->GetExp() / (float)Player::EXP_TABLE[_player->GetLevel() - 1]);

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

  delete eventHistory;

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
        if(event.key.keysym.sym == SDLK_0)
          eventHistory->LogEvent("Item gained.");
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
      SaveSavegame();
      _ingameMenu.SetStatus(false);
      Debug::logger->message("Game Saved!");
      break;
    case ingameMenuLoadGame:
      LoadSavegame(_saveGameID);
      _ingameMenu.SetStatus(false);
      Debug::logger->message("Game Loaded!");
      break;
    case ingameMenuOptions:
      break;
    case ingameMenuMainMenu:
      SDL_FillRect(screen, NULL, 0);
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
  UpdateInput();
  if(_ingameMenu.GetStatus() == false) {
    _map.Update();
    _player->Update();

    if(gameOver) {
      gameOver = false;

      _map.New();
      _player->SetHealth(100);
      _player->SetLevelLiteral(1);
      _player->SetExpLiteral(0);

      New(_saveGameID);
    }

  } else {
    // :D
  }

}

void Game::Render(void) {
  //SDL_FillRect(screen, NULL, 0);
  if(_ingameMenu.GetStatus() == false) {
    _map.Render();
    _player->Render();

    _playerHealthBar.DrawLiteral();
    _playerHealth.RenderLiteral();

    _playerExpBar.DrawLiteral();
    _playerExp.RenderLiteral();

    if(debugEnabled) {
      _gameRenderTime.RenderLiteral();
      _gameUpdateTime.RenderLiteral();
      _playerXY.RenderLiteral();
      _npcHealth.RenderLiteral();
    }

    eventHistory->Render();

  } else {
    _ingameMenu.Render();
  }
  SDL_Flip(screen);
}

void Game::NewSavegame(const string savegameIDArg) {
  string saveFilename = "../Save/" + savegameIDArg;

  _map.New();
  _map.Save(_saveGameID);

  TiXmlDocument doc;

  TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");

  TiXmlElement* saveElement = new TiXmlElement("save");

  TiXmlElement* nameElement = new TiXmlElement("name");
  TiXmlText* nameText = new TiXmlText("Allanis"); //TODO: replace with _player->GetName() when it works.
  nameElement->LinkEndChild(nameText);

  int spawnX;
  int spawnY;
  _map.FindSpawnPoint(spawnX, spawnY, 40, 45);

  _player->SetXY(spawnX, spawnY);

  std::stringstream xString;
  xString << spawnX;

  TiXmlElement* xElement = new TiXmlElement("x");
  TiXmlText* xText = new TiXmlText(xString.str().c_str());
  xElement->LinkEndChild(xText);

  std::stringstream yString;
  yString << spawnY;

  TiXmlElement* yElement = new TiXmlElement("y");
  TiXmlText* yText = new TiXmlText(yString.str().c_str());
  yElement->LinkEndChild(yText);

  _player->SetLevelLiteral(1);

  TiXmlElement* levelElement = new TiXmlElement("level");
  TiXmlText* levelText = new TiXmlText("1");
  levelElement->LinkEndChild(levelText);

  _player->SetExpLiteral(0);

  TiXmlElement* expElement = new TiXmlElement("exp");
  TiXmlText* expText = new TiXmlText("0");
  expElement->LinkEndChild(expText);

  TiXmlElement* healthElement = new TiXmlElement("health");
  TiXmlText* healthText = new TiXmlText("100");
  healthElement->LinkEndChild(healthText);

  TiXmlElement* mapElement = new TiXmlElement("map");
  TiXmlText* mapText = new TiXmlText("map"); //TODO: replace with actual map name.
  mapElement->LinkEndChild(mapText);

  saveElement->LinkEndChild(nameElement);
  saveElement->LinkEndChild(xElement);
  saveElement->LinkEndChild(yElement);
  saveElement->LinkEndChild(levelElement);
  saveElement->LinkEndChild(expElement);
  saveElement->LinkEndChild(healthElement);
  saveElement->LinkEndChild(mapElement);

  doc.LinkEndChild(decl);
  doc.LinkEndChild(saveElement);

  doc.SaveFile(saveFilename.c_str());
}

void Game::LoadSavegame(const string savegameIDArg) {
  _saveGameID = savegameIDArg;
  string saveFilename = "../Save/" + _saveGameID;

  // Converting to XML ftw!
  TiXmlDocument mapFile(saveFilename.c_str());

  // Create new save if can't load file.
  if(!mapFile.LoadFile()) {
    New(savegameIDArg);
    return;
  }

  TiXmlElement* rootElem = NULL;
  TiXmlElement* dataElem = NULL;

  // <save> - Grab a save file.
  rootElem = mapFile.FirstChildElement("save");
  assert(rootElem != NULL);
  if(rootElem) {
    // <name> - Parse the player name.
    dataElem = rootElem->FirstChildElement("name");
    assert(dataElem != NULL);

    // Overloaded new/delete operator takes this out of scope..
    // TODO: Fix.
    //_player->SetName(dataElem->GetText());
    // </name>

    /*
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
        _player->SetXY((float)playerX, (float)playerY);
*/

    // <level> - Parse the player level.
    dataElem = dataElem->NextSiblingElement("level");
    assert(dataElem != NULL);
    int playerLevel = atoi(dataElem->GetText());
    // </level>

    _player->SetLevelLiteral(playerLevel);

    // <exp> - Parse the player exp.
    dataElem = dataElem->NextSiblingElement("exp");
    assert(dataElem != NULL);
    int playerExp = atoi(dataElem->GetText());
    // </exp>

    _player->SetExpLiteral(playerExp);

    // <health> - Parse the player health.
    dataElem = dataElem->NextSiblingElement("health");
    assert(dataElem != NULL);
    int playerHealth = atoi(dataElem->GetText());
    // </health>

    _player->SetHealthLiteral(playerHealth);
  }
  // <save>

  // </save>

  _map.Load(_saveGameID);
}

void Game::SaveSavegame(void) {
  string saveFilename = "../Save/" + _saveGameID;

  TiXmlDocument doc;

  TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");

  TiXmlElement* saveElement = new TiXmlElement("save");

  TiXmlElement* nameElement = new TiXmlElement("name");
  TiXmlText* nameText = new TiXmlText("Allanis"); //TODO: replace with _player->GetName() when it works. --konom
  nameElement->LinkEndChild(nameText);

  /*
    std::stringstream xString;
    xString << _player->GetX();

    TiXmlElement* xElement = new TiXmlElement("x");
    TiXmlText* xText = new TiXmlText(xString.str().c_str());
    xElement->LinkEndChild(xText);

    std::stringstream yString;
    yString << _player->GetY();

    TiXmlElement* yElement = new TiXmlElement("y");
    TiXmlText* yText = new TiXmlText(yString.str().c_str());
    yElement->LinkEndChild(yText);
*/

  std::stringstream levelString;
  levelString << _player->GetLevel();

  TiXmlElement* levelElement = new TiXmlElement("level");
  TiXmlText* levelText = new TiXmlText(levelString.str().c_str());
  levelElement->LinkEndChild(levelText);

  std::stringstream expString;
  expString << _player->GetExp();

  TiXmlElement* expElement = new TiXmlElement("exp");
  TiXmlText* expText = new TiXmlText(expString.str().c_str());
  expElement->LinkEndChild(expText);

  std::stringstream healthString;
  healthString << _player->GetHealth();

  TiXmlElement* healthElement = new TiXmlElement("health");
  TiXmlText* healthText = new TiXmlText(healthString.str().c_str());
  healthElement->LinkEndChild(healthText);

  saveElement->LinkEndChild(nameElement);
  //saveElement->LinkEndChild(xElement);
  //saveElement->LinkEndChild(yElement);
  saveElement->LinkEndChild(levelElement);
  saveElement->LinkEndChild(expElement);
  saveElement->LinkEndChild(healthElement);

  doc.LinkEndChild(decl);
  doc.LinkEndChild(saveElement);

  doc.SaveFile(saveFilename.c_str());

  _map.Save(_saveGameID);
}
