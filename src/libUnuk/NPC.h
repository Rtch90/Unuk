#ifndef _NPC_H_
#define _NPC_H_

#include "Character.h"

class NPC : public Character {
public:
  NPC(Map* mapArg);
  ~NPC(void);
  
  void Update(void);
  
protected:
  void Move(void);
  
private:
  int m_moveChangeFrequency;
  
  int m_moveDurationCurrent;
  int m_moveDurationMin;
  int m_moveDurationMax;
  
  bool m_moving;
  
  Timer m_moveTimer;
};

#endif