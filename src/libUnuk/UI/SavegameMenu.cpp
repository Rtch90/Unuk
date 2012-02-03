#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <sstream>

#include "SavegameMenu.h"
#include "../../Unuk/Globals.h"

SavegameMenu::SavegameMenu(void) {
  _title.SetXY(BOX_SPACING_X, 25);
  _title.SetTextBlended("Choose Savegame: ", vlarge, 0, 255, 255);
  
  for(int i = 0; i < 4; i++) {
    std::stringstream capText;
    if(i != 3) {
      capText << "Savegame " << i;
    } else {
      capText << "Cancel";
    }
    
    _captions[i].SetXY(BOX_SPACING_X + BOX_WIDTH/2,
                       BOXES_OFFSET_Y + (i * BOX_SPACING_Y) + (i * BOX_HEIGHT) + BOX_HEIGHT/2);
    
    _captions[i].SetTextBlended(capText.str(), large, 0, 255, 255);
    
    _captions[i].SetXY(_captions[i].GetX() - _captions[i].GetWidth()/2,
                       _captions[i].GetY() - _captions[i].GetHeight()/2);
  }
  
  _selection = 0;
}

SavegameMenu::~SavegameMenu(void) {
}

savegameMenuNavVal_t SavegameMenu::Run(void) {
  SDL_FillRect(screen, NULL, 0);
  
  while(true) {
    Render();
    SDL_Flip(screen);
    
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_QUIT:
        return savegameMenuQuit;
      case SDL_KEYUP:
        if(event.key.keysym.sym == SDLK_UP) {
          _selection--;
          if(_selection < 0) {
            _selection = 3;
          }
        } else if(event.key.keysym.sym == SDLK_DOWN) {
          _selection++;
          if(_selection > 3) {
            _selection = 0;
          }
        } else if(event.key.keysym.sym == SDLK_RETURN) {
          return savegameMenuSave;
        }
        break;
      }
    }
  }
  
  return savegameMenuCancel;
}

void SavegameMenu::Render(void) {
  _title.RenderLiteral();
  
  for(int i = 0; i < 4; i++) {
    int borderRed;
    int borderGreen;
    int borderBlue;
    
    if(i == _selection) {
      borderRed = 255;
      borderGreen = 128;
      borderBlue = 0;
    } else {
      borderRed = 0;
      borderGreen = 255;
      borderBlue = 255;
    }
    
    roundedBoxRGBA(screen,
            BOX_SPACING_X,             BOXES_OFFSET_Y + (i * BOX_SPACING_Y) + (i * BOX_HEIGHT),
            BOX_SPACING_X + BOX_WIDTH, BOXES_OFFSET_Y + (i * BOX_SPACING_Y) + (i * BOX_HEIGHT) + BOX_HEIGHT,
            5,
            0, 0, 128, 255);
    
    roundedRectangleRGBA(screen,
                  BOX_SPACING_X,             BOXES_OFFSET_Y + (i * BOX_SPACING_Y) + (i * BOX_HEIGHT),
                  BOX_SPACING_X + BOX_WIDTH, BOXES_OFFSET_Y + (i * BOX_SPACING_Y) + (i * BOX_HEIGHT) + BOX_HEIGHT,
                  5,
                  borderRed, borderGreen, borderBlue, 255);
    
    _captions[i].RenderLiteral();
  }
}
