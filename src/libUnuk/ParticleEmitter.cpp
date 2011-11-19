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
  for(int i = 0; i < m_particleCount; i++) {
    m_particle[i].x = xArg;
    m_particle[i].y = yArg;
  }
}

void ParticleEmitter::SetParticleCount(int countArg) {
  m_particleCount = countArg;
  m_particle.resize(m_particleCount);

  for(int i = 0; i < m_particleCount; i++) {
    m_particle[i].startTime = SDL_GetTicks();
  }
}

void ParticleEmitter::SetParticleSpeed(float speedArg) {
  m_particleSpeed = speedArg;
}

void ParticleEmitter::SetParticleType(string typeArg) {
  if(!particleTexture) {
    SDL_FreeSurface(particleTexture);
  }

  string textureFilename = "../Data/Media/Images/Particles/" + typeArg + ".png";
  particleTexture = LoadImageAlpha(textureFilename.c_str());
}

void ParticleEmitter::SetParticleLifetime(int lifetimeArg) {
  m_particleLifetime = lifetimeArg;

  for(int i = 0; i < m_particleCount; i++) {
    m_particle[i].lifetime = rand() % m_particleLifetime + m_particleLifetime / 4;
  }
}

void ParticleEmitter::Render(void) {
  for(int i = 0; i < m_particleCount; i++) {
    ApplySurface(m_particle[i].x, m_particle[i].y, particleTexture, screen);
  }
}

void ParticleEmitter::Update(void) {
  for(int i = 0; i < m_particleCount; i++) {
    if((int)SDL_GetTicks() - m_particle[i].startTime > m_particle[i].lifetime) {
      // Reset the x and y coords.
      m_particle[i].x = x;
      m_particle[i].y = y;

      m_particle[i].xVel = rand() % 360;
      m_particle[i].yVel = rand() % 360;

      if(rand() % 2)
        m_particle[i].xVel = m_particle[i].xVel * -1;
      if(rand() % 2)
        m_particle[i].yVel = m_particle[i].yVel * -1;

      m_particle[i].startTime = SDL_GetTicks();
    } else {
      m_particle[i].x += m_particle[i].xVel * m_particleSpeed;
      m_particle[i].y += m_particle[i].yVel * m_particleSpeed;
    }
  }
}
