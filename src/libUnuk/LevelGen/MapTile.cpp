#include "MapTile.h"

void MapTile::Deflate(Serialiser* serialiser) {
  string  tileTexture    = _tile.GetTextureName();
  bool    solidTile      = _tile.GetSolidity();
  string  entityTexture  = _entity.GetTextureName();
  bool    solidEntity    = _entity.GetSolidity();

  if(tileTexture.empty()) {
    tileTexture = "null";
  }
  if(entityTexture.empty()) {
    entityTexture = "null";
  }

  serialiser->RegisterMember("tileTexture",   MEMBER_STRING,  &tileTexture);
  serialiser->RegisterMember("solidTile",     MEMBER_BOOL,    &solidTile);
  serialiser->RegisterMember("entityTexture", MEMBER_STRING,  &entityTexture);
  serialiser->RegisterMember("solidEntity",   MEMBER_BOOL,    &solidEntity);

  serialiser->WriteMembers();
}

void MapTile::Inflate(Serialiser* serialiser) {
  string  tileTexture;
  bool    solidTile;
  string  entityTexture;
  bool    solidEntity;

  serialiser->RegisterMember("tileTexture",   MEMBER_STRING,  &tileTexture);
  serialiser->RegisterMember("solidTile",     MEMBER_BOOL,    &solidTile);
  serialiser->RegisterMember("entityTexture", MEMBER_STRING,  &entityTexture);
  serialiser->RegisterMember("solidEntity",   MEMBER_BOOL,    &solidEntity);

  serialiser->ReadMembers();

  _tile.SetTextureName(tileTexture);
  _tile.SetSolidity(solidTile);

  _entity.SetTextureName(entityTexture);
  _entity.SetSolidity(solidEntity);
}
