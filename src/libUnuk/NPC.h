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
  int _moveChangeFrequency;
  
  int _moveDurationCurrent;
  int _moveDurationMin;
  int _moveDurationMax;
  
  bool _moving;
  
  Timer _moveTimer;
};

#endif
