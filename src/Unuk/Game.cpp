#include "Game.h"

Game::Game(void) {
  m_player = new Player(&m_map);
  m_npc = new NPC(&m_map);

  m_runGameReturnValue = GAME_RETURN_TO_MMENU;
}

Game::~Game(void) {
  delete m_player;
  delete m_npc;
}

int Game::Run(const string savegameIDArg) {
  m_player->SetXY(100, 50);
  m_player->LoadSprites("../Data/Media/Images/Characters/template.png", 40, 45);

  m_npc->SetXY(300, 300);
  m_npc->LoadSprites("../Data/Media/Images/Characters/template.png", 40,45);

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

  m_gameRenderTime.SetXY(10, 10);
  m_gameRenderTime.SetTextBlended("Render - XX", "vsmall", COLOUR_BLACK);

  m_gameUpdateTime.SetXY(10, 30);
  m_gameUpdateTime.SetTextBlended("Update - XX", "vsmall", COLOUR_BLACK);

  stringstream playerXYString;
  m_playerXY.SetXY(10, 50);
  m_playerXY.SetTextBlended("Player coords - XX XX", "vsmall", COLOUR_BLACK);

  m_gameRunning = true;
  while(m_gameRunning) {
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
        m_gameUpdateTime.SetTextBlended("Update - " + updateTimer.GetTicksStr(), "vsmall", COLOUR_BLACK);
        m_gameRenderTime.SetTextBlended("Render - " + renderTimer.GetTicksStr(), "vsmall", COLOUR_BLACK);

        playerXYString.str("");
        playerXYString << "Player coords: x" << m_player->GetX() << ", y" << m_player->GetY();
        m_playerXY.SetTextBlended(playerXYString.str(), "vsmall", COLOUR_BLACK);
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
  return m_runGameReturnValue;
}

void Game::HandleInput(void) {
  if(m_ingameMenu.GetStatus() == false) {
    while(SDL_PollEvent(&event)) {
      m_player->HandleInput();

      if(event.key.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_ESCAPE)
          m_ingameMenu.SetStatus(true);
        if(event.key.keysym.sym == SDLK_p)
          debugEnabled = !debugEnabled;
      }
      else if(event.type == SDL_QUIT) {
        m_gameRunning = false;
        m_runGameReturnValue = GAME_QUIT_GAME;
        break;
      }
    }
  } else {
    switch(m_ingameMenu.HandleInput()) {
    case INGAME_MENU_NOTHING:
      break;
    case INGAME_MENU_RESUME:
      m_ingameMenu.SetStatus(false);
      break;
    case INGAME_MENU_SAVE_GAME:
      break;
    case INGAME_MENU_LOAD_GAME:
      break;
    case INGAME_MENU_OPTIONS:
      break;
    case INGAME_MENU_EXIT_TO_MMENU:
      m_gameRunning = false;
      break;
    }

    if(event.type == SDL_QUIT) {
      m_gameRunning = false;
      m_ingameMenu.SetStatus(false);
      m_runGameReturnValue = GAME_QUIT_GAME;
    }
  }
}

void Game::UpdateGame(void) {
  if(m_ingameMenu.GetStatus() == false) {
    m_player->Update();
    m_npc->Update();
  } else {
    // :D
  }
}

void Game::Render(void) {
  if(m_ingameMenu.GetStatus() == false) {
    m_map.Render();

    m_player->Render();
    m_npc->Render();

    if(debugEnabled) {
      m_gameRenderTime.RenderLiteral();
      m_gameUpdateTime.RenderLiteral();
      m_playerXY.RenderLiteral();
    }
  } else {
    m_ingameMenu.Render();
  }
  SDL_Flip(screen);
  SDL_Flip(screen);
}

void Game::LoadSavegame(const string savegameIDArg) {
  m_saveGameID = savegameIDArg;

  string saveFilename = "../Save/" + m_saveGameID;

  ifstream saveFile(saveFilename.c_str());
  assert(saveFile.is_open());

  // Read stuff.
  m_map.Load("TestLevel");
}

void Game::SaveSavegame(void) {
  string saveFilename = "../Save/" + m_saveGameID;

  ofstream saveFile(saveFilename.c_str());
  assert(saveFile.is_open());

  // Write stuff.
}
