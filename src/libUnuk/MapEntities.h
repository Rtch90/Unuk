#ifndef _MAPENTITIES_H_
#define _MAPENTITIES_H_

#include "MapElement.h"

class MapEntityGeneric : public MapElement {
public:
  MapEntityGeneric(void);
  ~MapEntityGeneric(void);

  void Render(void);

private:

};

#endif
