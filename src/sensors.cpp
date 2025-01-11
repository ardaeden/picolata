#include "sensors.hpp"
#include <hardware/adc.h>
#include <pico/cyw43_arch.h>


// A SIMPLE POTENTIOMETER
Pot::Pot(uint8_t adcPin) {
  _adcPin = adcPin;
  adc_init();
  adc_gpio_init(_adcPin);
}

uint16_t Pot::getRawValue() {
  adc_select_input(_adcPin-26);
  _reading = adc_read();
  return _reading;
}

uint8_t Pot::getMidiValue() {
  adc_select_input(_adcPin-26);
  _reading = adc_read();
  _reading >>= 5;
  return _reading;
}
