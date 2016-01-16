#include <ExtendedDHT.h>
#include <Arduino.h>

ExtendedDHT::ExtendedDHT(uint8_t dht_pin, uint8_t dht_type)  : dht(dht_pin, dht_type) {
  this->temperature, this->humidity = 0;
  this->last_read = millis();
  this->failed = false;
}

void ExtendedDHT::begin() {
  this->dht.begin();
}

float ExtendedDHT::getTemperature() {
  pollDHT();
  return this->temperature;
}

float ExtendedDHT::getHumidity() {
  pollDHT();
  return this->humidity;
}

bool ExtendedDHT::canPoll() {
  if(millis() - this->last_read < 2000)
    return false;
  else
    return true;
}

void ExtendedDHT::pollDHT() {
  // Checking too soon
  if(!canPoll()) {
    return;
  }
  // Update last read at
  this->last_read = millis();
  float h = this->dht.readHumidity();
  float t = this->dht.readTemperature();
  if(isnan(h) || isnan(t)) {
    // Failed to read
    this->failed = true;
#ifdef DHT_DEBUG
    Serial.println("Failed to poll!!!!");
#endif
    return;
  } else {
    this->failed = false;
  }
  this->humidity = h;
  this->temperature = t;
#ifdef DHT_DEBUG
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("");
#endif
}
