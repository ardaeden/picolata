#include "sensors.hpp"
#include "network.hpp"
#include "tinyosc.hpp"
#include <pico/stdlib.h> // IWYU pragma: keep
#include <pico/time.h>
#include <stdint.h>

int main() {
  // Initialize stdio for printf
  stdio_init_all();
  // Have to wait a bit to be able to use printf
  sleep_ms(1000);

  // Initialize app
  if (!Network::initialize()) {
    printf("Failed to initialize!");
    return -1;
  }

  // OSC parameters
  char dest_addr[] = "255.255.255.255";
  const unsigned int port = 3333;
  // Empty buffer to put the message into
  char buffer[1024];

  // Initialize osc
  TinyOSC osc = TinyOSC();

  // Create pots
  Pot pot1 = Pot(ADC0);
  Pot pot2 = Pot(ADC2);
  
  // App start
  printf("Entering main loop.");
  // Set the desired loop frequency (n times per second)
  const int n = 500;   // for example, 10Hz
  const int interval_ms = 1000 / n; // Convert frequency to milliseconds

  // LOOP
  while (true) {
    // Record the start time
    //uint32_t start_time = to_ms_since_boot(get_absolute_time());

    // Your main loop code goes here
    osc.writeMessage(buffer, sizeof(buffer), "/pot_1", "i", pot1.getMidiValue());
    Network::send(buffer, dest_addr, port);

    osc.writeMessage(buffer, sizeof(buffer), "/pot_2", "i", pot2.getMidiValue());
    Network::send(buffer, dest_addr, port);

    // Calculate elapsed time
    //uint32_t elapsed_time = to_ms_since_boot(get_absolute_time()) - start_time;

    // Check if the loop overran
    //if (elapsed_time > interval_ms) {
    //  printf("overrun\n");
    //} else {
    //  // Sleep until the next loop cycle
    //  sleep_ms(interval_ms - elapsed_time);
    //}
  }

  printf("Exiting");
  Network::deinitialize();
  sleep_ms(1000);

  return 0;
}
