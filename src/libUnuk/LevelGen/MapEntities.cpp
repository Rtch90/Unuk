#include "MapEntities.h"

MapEntityGeneric::MapEntityGeneric(void) {
  _texture = NULL;

}

MapEntityGeneric::~MapEntityGeneric(void) {

}

void MapEntityGeneric::Render(void) {
  if(_texture != NULL) {
    MapElement::Render();
  }
}
