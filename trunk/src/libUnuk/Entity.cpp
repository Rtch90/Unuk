#include "Entity.h"

Entity::Entity(GameWorld* const gameWorld) :
    m_canBeRemoved(false),
    m_world(gameWorld) {}

Entity::~Entity(void) {}

bool Entity::CanBeRemoved(void) const {
  return m_canBeRemoved;
}

void Entity::Destroy(void) {
  m_canBeRemoved = true;
}

void Entity::Prepare(float dt) {
  OnPrepare(dt);
}

void Entity::Render(void) const {
  OnRender();
}

void Entity::OnPostRender(void) {
  OnPostRender();
}

bool Entity::Initialize(void) {
  return OnInitiaize();
}

void Entity::Shutdown(void) {
  OnShutdown();
}
