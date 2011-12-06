#include "NPC.h"

NPC::NPC(Map* mapArg) : Character(mapArg) {
  m_moveTimer.Start();
  
  m_moveChangeFrequency = 14000;
  m_moveDurationMax	= 3000;
  m_moveDurationMin	= 1000;
}

NPC::~NPC(void) {

}

void NPC::Update(void) {
  Move();
}

void NPC::Move(void) {
  if(m_moving && m_moveTimer.GetTicks() > m_moveDurationMax) {
    xVel = 0.0f;
    yVel = 0.0f;
    m_moving = false;
  }
  
  if(m_moving && m_moveTimer.GetTicks() >= m_moveDurationCurrent) {
    xVel = 0.0f;
    yVel = 0.0f;
    m_moving = false;
  }
  
  if(m_moveTimer.GetTicks() > m_moveChangeFrequency) {
    m_moveTimer.Start();
    m_moveDurationCurrent = m_moveDurationMin + (rand() % (m_moveDurationMax - m_moveDurationMin));
    if(rand() % 2) {
      yVel = 0.0f;
      if(rand() % 2)
        xVel = CHARACTER_SPEED;
      else
        xVel = -CHARACTER_SPEED;
    } else {
      xVel = 0.0f;
      if(rand() % 2)
        yVel = CHARACTER_SPEED;
      else
        yVel = -CHARACTER_SPEED;
    }
    m_moving = true;
  }
  Character::Move();
}
