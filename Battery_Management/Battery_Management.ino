// Defining the battery monitoring variables
float Voltage, Current, BatteryRemaining, BatteryatStart;
float CurrentConsumed = 0;
float BatteryDefault = 1300;

//Measure the voltage and current of the circuit
void battery_voltage(void)
{
  Voltage = (float)analogRead(15)/62;
  Current = (float)analogRead(21)*0.089;
}

// Determine the battery capacity prior to the flight
void setup()
{
  digitalWrite(5, HIGH)
  {
    battery_voltage();
    if(Voltage > 8.3)
    {
      digitalWrite(5, LOW);
      BatteryatStart = BatterDefault;
    }
    else if(Voltage < 7.5)
    {
      BatteryatStart = 30*100/BatteryDefault;
    }
    else
    {
      digitalWrite(5, LOW);
      BatteryatStart = (82 * Voltage -580) / 100 * BatteryDefault;
    }
  }
}

void loop
{
  // Calculate the battery capacity during flight
  battery_voltage();
  CurrentConsumed = Current * 1000 * 0.004 / 3600 + CurrentConsumed;
  BatteryRemaining = (BatteryatStart - CurrentConsumed)/BatteryDefault*100;
  if (batteryRemaining < 30)
  {
    digitalWrite(5, HIGH);
  }
  else
  {
    digitalWrite(5, LOW);
  }
}