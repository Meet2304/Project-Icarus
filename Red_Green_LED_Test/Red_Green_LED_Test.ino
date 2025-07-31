void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Turning on the RED LED
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);

  // Delay of 4000 milisec
  delay(4000);
  // Turning OFF the RED LED
  digitalWrite(5, LOW);
  // Turning ON the GREEN LED
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:

}
