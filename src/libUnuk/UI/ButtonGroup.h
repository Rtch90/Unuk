#pragma once
#include <list>

#include "../UI/Button.h"

class ButtonGroup {
public:
  ButtonGroup(void);
  ~ButtonGroup(void);

  void  CheckMouseOverDummy(void);
  int   CheckMouseOver(void);

  void RenderLiteral(void);

  void AddButton(Button* button);
  void RemoveButton(int index);

  void SelectNext(void);
  void SelectPrevious(void);

  int   GetSelectedButton(void)         { return _selectedButton; }
  void  SetSelectedButton(int button);

  Button* GetButton(int index);

private:
  void HighlightNewSelection(int newButton);

  std::list<Button*> _buttons;
  int _selectedButton;
};
