#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "Geometry.h"
#include "EntityType.h"
#include "Static.h"

class GameWorld;

/*
 * Entity is static because we will mainly be handling
 * pointers (that can be copied around) but we want
 * all entities to be initiaized by the gameworld.
 */

class Entity : private Static {
public:
  Entity(GameWorld* const gameWorld);
  virtual ~Entity(void);

  void Prepare(float dt);
  void Render(void) const;
  void PostRender(void);
  bool Initialize(void);
  void Shutdown(void);
  bool CanBeRemoved(void) const;
  void Destroy(void);

  virtual Vector2 GetPosition(void) const = 0;
  //virtual Vector2 GetVelocity() const = 0;
  virtual void SetPosition(const Vector2& position) = 0;

  virtual EntityType GetType(void) const = 0;

private:
  virtual void OnPrepare(float dt)    = 0;
  virtual void OnRender(void) const   = 0;
  virtual void OnPostRender(void)     = 0;
  virtual bool OnInitiaize(void)      = 0;
  virtual void OnShutdown(void)       = 0;

  bool m_canBeRemoved;

  GameWorld* m_world;
};

#endif
