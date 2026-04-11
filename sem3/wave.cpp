#include "wave.h"
#include "DynamicArray.h"
#include <cmath>

AcousticWave::AcousticWave(double frequency, double amplitude,
                           unsigned int sampleRate)
    : frequency(frequency), amplitude(amplitude), sampleRate(sampleRate) {}

SineWave::SineWave(double frequency, double amplitude, unsigned int sampleRate)
    : AcousticWave(frequency, amplitude, sampleRate) {}

void SineWave::computeSamples(float duration) {
  double t = 0.0;
  samples = DynamicArray(sampleRate * duration);
  for (unsigned int i = 0; i < samples.getCapacity(); i++) {
    samples[i] = amplitude * std::sin(2.0 * M_PI * frequency * t * frequency);
    t += 1.0 / sampleRate;
  }
}
