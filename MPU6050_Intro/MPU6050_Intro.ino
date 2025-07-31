#include <Wire.h>

// Declaring variables to collect data from the sensors
float RateRoll, RatePitch, RateYaw;

void gyro_signals() {
  Wire.beginTransmission(0x68);  // Start I2C communication with the MPU6050
  Wire.write(0x1A);              // Accessing the configuration register
  Wire.write(0x05);              // Setting the low pass filter to 10Hz cut-off frequency
  Wire.endTransmission();

  // Setting the sensitivity scale factor
  Wire.beginTransmission(0x68);  
  Wire.write(0x1B);             // Accessing the gyroscope configuration register   
  Wire.write(0x08);             // Setting the sensitivity to 65.5 degrees per second
  Wire.endTransmission();

  // Requesting measurements from the gyro
  Wire.beginTransmission(0x68);
  Wire.write(0x43);             // Starting register for gyro measurements
  Wire.endTransmission();
  Wire.requestFrom(0x68, 6);    // Requesting 6 bytes of data

  if (Wire.available() == 6) {  // Ensure 6 bytes were received
    int16_t GyroX = Wire.read() << 8 | Wire.read();  // Reading gyro X-axis data
    int16_t GyroY = Wire.read() << 8 | Wire.read();  // Reading gyro Y-axis data
    int16_t GyroZ = Wire.read() << 8 | Wire.read();  // Reading gyro Z-axis data

    // Converting measurements to degrees per second
    RateRoll = (float)GyroX / 65.5;
    RatePitch = (float)GyroY / 65.5;
    RateYaw = (float)GyroZ / 65.5;
  }
}

void setup() {
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Wire.setClock(400000);    // Setting I2C clock speed to 400kHz
  Wire.begin();
  delay(250);

  // Activating the MPU6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);         // Accessing the power management register
  Wire.write(0x00);         // Setting the device to wake up
  Wire.endTransmission();
}

void loop() {
  // Call the predefined function to read the gyro measurements
  gyro_signals();
  Serial.print("Roll Rate (deg/sec): ");
  Serial.print(RateRoll);
  Serial.print("\tPitch Rate (deg/sec): ");
  Serial.print(RatePitch);
  Serial.print("\tYaw Rate (deg/sec): ");
  Serial.println(RateYaw);
  delay(50);  // Adding delay to read the values in the serial monitor
}
