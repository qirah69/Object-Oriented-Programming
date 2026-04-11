#pragma once
#include "DynamicArray.h"

class AcousticWave {
protected:
  double frequency;
  double amplitude;
  unsigned int sampleRate;
  DynamicArray samples;

public:
  AcousticWave(double frequency, double amplitude, unsigned int sampleRate);
  virtual void computeSamples(float duration);
};

class SineWave : public AcousticWave {
public:
  SineWave(double frequency, double amplitude, unsigned int sampleRate);

  void computeSamples(float duration);
};
