// Using the Pulse Position Library
#include <PulsePosition.h>

// Creating a PPM Input object
PulsePositionInput ReceiverInput(RISING);

// Declare the variables to store channel info
float ReceiverValue[] = {0,0,0,0,0,0,0,0};
int ChannelNumber = 0;

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
}

// Read and Display PPM information on the Serial Monitor
void loop()
{
  read_receiver();
  
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
