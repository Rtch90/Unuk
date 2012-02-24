#pragma once
#include <stdio.h>

class Serialiser;

class Serialisable {
public:
  virtual void Deflate(Serialiser* serialiser) = 0;
  virtual void Inflate(Serialiser* serialiser) = 0;
};
