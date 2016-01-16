#ifndef extended_dht_h
#define extended_dht_h
#include <stdint.h>
#include <DHT.h>

/**
 * Extended DHT library
 *
 * Dependancies:
 *    https://github.com/adafruit/DHT-sensor-library
 */
#define DHT_DEBUG

class ExtendedDHT {
  DHT dht;
  float temperature, humidity;
  unsigned long last_read;
  bool failed;

public:
  ExtendedDHT(uint8_t, uint8_t);
  void begin();
  float getTemperature();
  float getHumidity();

private:
  bool canPoll();
  void pollDHT();
};

#endif
