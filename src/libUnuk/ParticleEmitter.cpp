#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(void) {

}

ParticleEmitter::~ParticleEmitter(void) {

}

void ParticleEmitter::SetXY(int xArg, int yArg) {
  x = xArg;
  y = yArg;
}

void ParticleEmitter::ForceXY(int xArg, int yArg) {
  for(int i = 0; i < _particleCount; i++) {
    m_particle[i].x = (float)xArg;
    m_particle[i].y = (float)yArg;
  }
}

void ParticleEmitter::SetParticleCount(int countArg) {
  _particleCount = countArg;
  m_particle.resize(_particleCount);

  for(int i = 0; i < _particleCount; i++) {
    m_particle[i].startTime = SDL_GetTicks();
  }
}

void ParticleEmitter::SetParticleSpeed(float speedArg) {
  _particleSpeed = speedArg;
}

void ParticleEmitter::SetParticleType(string typeArg) {
  if(!_particleTexture) {
    SDL_FreeSurface(_particleTexture);
  }

  string textureFilename = "../Data/Media/Images/Particles/" + typeArg + ".png";
  _particleTexture = LoadImageAlpha(textureFilename.c_str());
}

void ParticleEmitter::SetParticleLifetime(int lifetimeArg) {
  _particleLifetime = lifetimeArg;

  for(int i = 0; i < _particleCount; i++) {
    m_particle[i].lifetime = rand() % _particleLifetime + _particleLifetime / 4;
  }
}

void ParticleEmitter::Render(void) {
  for(int i = 0; i < _particleCount; i++) {
    ApplySurface((int)m_particle[i].x, (int)m_particle[i].y, _particleTexture, screen);
  }
}

void ParticleEmitter::Update(void) {
  for(int i = 0; i < _particleCount; i++) {
    if((int)SDL_GetTicks() - m_particle[i].startTime > m_particle[i].lifetime) {
      // Reset the x and y coords.
      m_particle[i].x = (float)x;
      m_particle[i].y = (float)y;

      m_particle[i].xVel = (float)(rand() % 360);
      m_particle[i].yVel = (float)(rand() % 360);

      if(rand() % 2)
        m_particle[i].xVel = m_particle[i].xVel * -1.0f;
      if(rand() % 2)
        m_particle[i].yVel = m_particle[i].yVel * -1.0f;

      m_particle[i].startTime = SDL_GetTicks();
    } else {
      m_particle[i].x += m_particle[i].xVel * _particleSpeed;
      m_particle[i].y += m_particle[i].yVel * _particleSpeed;
    }
  }
}
