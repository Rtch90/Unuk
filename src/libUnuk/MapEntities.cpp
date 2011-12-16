#include "MapEntities.h"

MapEntityGeneric::MapEntityGeneric(void) {
  m_texture = NULL;

}

MapEntityGeneric::~MapEntityGeneric(void) {

}

void MapEntityGeneric::Render(void) {
  if(m_texture != NULL) {
    MapElement::Render();
  }
}
