#include "ButtonGroup.h"

ButtonGroup::ButtonGroup(void) {
  _selectedButton = -1;
}

ButtonGroup::~ButtonGroup(void) {
  for(std::list<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i) {
    Button* btn = (*i);
    delete btn;
  }
}

void ButtonGroup::CheckMouseOverDummy(void) {
  for(std::list<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i) {
    (*i)->CheckMouseOver();
  }
}

int ButtonGroup::CheckMouseOver(void) {
  int buttonIndex = 0;
  for(std::list<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i) {
    if((*i)->CheckMouseOver()) {
      return buttonIndex;
    }
    buttonIndex++;
  }
  return -1;
}

void ButtonGroup::RenderLiteral(void) {
  for(std::list<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i) {
    (*i)->RenderLiteral();
  }
}

void ButtonGroup::AddButton(Button* button) {
  _buttons.push_back(button);
}

void ButtonGroup::RemoveButton(int index) {
  int buttonsIndex = 0;
  for(std::list<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i) {
    if(buttonsIndex == index) {
      _buttons.erase(i);
      break;
    }
    buttonsIndex++;
  }
}

void ButtonGroup::SelectNext(void) {
  if(_selectedButton == -1) {
    HighlightNewSelection(0);
  } else {
    HighlightNewSelection(_selectedButton + 1);
  }
}

void ButtonGroup::SelectPrevious(void) {
  if(_selectedButton == -1) {
    HighlightNewSelection(0);
  } else {
    HighlightNewSelection(_selectedButton - 1);
  }
}

void ButtonGroup::SetSelectedButton(int button) {
  HighlightNewSelection(button);
}

void ButtonGroup::HighlightNewSelection(int newButton) {
  if(_selectedButton != -1) {
    // Turn off highlight for currently highlighted button
    GetButton(_selectedButton)->SetHighlighted(false);
  }

  _selectedButton = newButton;

  // If < 0 then up was pressed when first index was selected
  // If >= _buttons.size() then down was pressed when last index was selected
  if(_selectedButton < 0) {
    _selectedButton = _buttons.size() - 1;
  } else if(_selectedButton >= (int)_buttons.size()) {
    _selectedButton = 0;
  }

  // Highlight new selection
  GetButton(_selectedButton)->SetHighlighted(true);
}

Button* ButtonGroup::GetButton(int index) {
  int buttonsIndex = 0;
  for(std::list<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i) {
    if(buttonsIndex == index) {
      return (*i);
    }
    buttonsIndex++;
  }
  return NULL;
}
