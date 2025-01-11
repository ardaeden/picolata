#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <stdint.h>

#define ADC0 26
#define ADC1 27
#define ADC2 28

class Pot {
public:
  Pot(uint8_t adcPin);
  ~Pot() = default;
  uint16_t getRawValue();
  uint8_t getMidiValue();

private:
  uint8_t _adcPin;
  uint16_t _reading;
};
#endif
