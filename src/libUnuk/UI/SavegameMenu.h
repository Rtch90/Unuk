#pragma once

#include "../UI/Text.h"

enum savegameMenuNavVal_t { savegameMenuSave, savegameMenuCancel, savegameMenuQuit };

class SavegameMenu
{
public:
  SavegameMenu(void);
  ~SavegameMenu(void);

  savegameMenuNavVal_t Run(void);

  int GetSelection(void) { return _selection; }

private:
  void Render(void);

  Text _title;
  Text _captions[4];
  int _selection;

  static const int BOX_WIDTH        = 400;
  static const int BOX_HEIGHT       = 100;
  static const int BOX_SPACING_X    = 25;
  static const int BOX_SPACING_Y    = 25;
  static const int BOXES_OFFSET_Y   = 100;
};
