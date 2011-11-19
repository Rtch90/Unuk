#ifndef _PARTICLEEMITTER_H_
#define _PARTICLEEMITTER_H_
#include <SDL/SDL.h>
#include <vector>
#include <string>
#include <sstream>

#include "../Unuk/Globals.h"
#include "ImageLoader.h"
#include "ApplySurface.h"
using namespace std;

struct Particle {
  float x;
  float y;

  float xVel;
  float yVel;

  int lifetime;
  int startTime;
};

class ParticleEmitter {
public:
  ParticleEmitter(void);
  ~ParticleEmitter(void);

  // distribute particles from the new x and y.
  void SetXY(int xArg, int yArg);
  // Move all the existing particles to the new x and y.
  void ForceXY(int xArg, int yArg);

  void SetParticleCount(int countArg);
  void SetParticleLifetime(int lifetimeArg);
  void SetParticleSpeed(float speedArg);
  void SetParticleType(string typeArg);

  void Render(void);
  void Update(void);

private:
  vector<Particle> m_particle;

  int x;
  int y;

  int     m_particleCount;
  int     m_particleLifetime;
  float   m_particleSpeed;

  SDL_Surface* particleTexture;
};

#endif
