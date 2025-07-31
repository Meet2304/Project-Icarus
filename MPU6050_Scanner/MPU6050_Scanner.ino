#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(57600);
  Serial.println("I2C Scanner");
}

void loop() {
  Serial.println("Scanning...");

  bool deviceFound = false;
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      deviceFound = true;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (!deviceFound) {
    Serial.println("No I2C devices found");
  }

  Serial.println("Scanning done");
  delay(2000); // Wait 2 seconds before next scan
}
