// Using the Pulse Position Library
#include <PulsePosition.h>

// Creating a PPM Input object
PulsePositionInput ReceiverInput(RISING);

// Declare the variables to store channel info
float ReceiverValue[] = {0,0,0,0,0,0,0,0};
int ChannelNumber = 0;
float InputThrottle;

// Defining a function to read the receiver data
void read_receiver(void)
{
  ChannelNumber = ReceiverInput.available();
  if (ChannelNumber > 0)
  {
    for (int i = 1; i <= ChannelNumber; i++)
    {
      ReceiverValue[i-1] = ReceiverInput.read(i);
    }
  }
}

void setup()
{
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  ReceiverInput.begin(14);
  
  // Sending PWM signals from teensy
  analogWriteFrequency(1, 250);
  
  // Set the PWM Resolution
  analogWriteResolution(12);
  delay(250);

  // Avoid Uncontrolled Motor Start
  while (ReceiverValue[2] < 1020 || ReceiverValue[2] > 1050)
  {
    read_receiver();
    delay(4);
  } 
}

// Read and Display PPM information on the Serial Monitor
void loop()
{
  read_receiver();
  InputThrottle = ReceiverValue[2];
  
  // Map the throttle value to PWM output range
  analogWrite(1, map(InputThrottle, 1000, 2000, 0, 4095)); // Assuming throttle values are between 1000 and 2000 us

  Serial.print("Number of Channels: ");
  Serial.print(ChannelNumber);
  
  Serial.print(" Roll[us]: ");
  Serial.print(ReceiverValue[0]);
  
  Serial.print(" Pitch[us]: ");
  Serial.print(ReceiverValue[1]);
  
  Serial.print(" Throttle[us]: ");
  Serial.print(ReceiverValue[2]);

  Serial.print(" Yaw[us]: ");
  Serial.println(ReceiverValue[3]);

  delay(50);
}
