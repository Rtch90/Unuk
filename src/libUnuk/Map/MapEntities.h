#pragma once
/*
 * Version of MapElement, that will check whether the SDL_Surface it
 * owns is NULL or not and draws.
 *
 */

#include "MapElement.h"

class MapEntityGeneric : public MapElement {
public:
  MapEntityGeneric(void);
  ~MapEntityGeneric(void);

  void Render(void);

private:

};
