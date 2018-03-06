
char serialData;
int pin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { // get the number of bytes available from the serial port
    serialData = Serial.read(); // read the data that is inputted
    Serial.println(serialData);
    if (serialData == '1') {
      digitalWrite(pin, HIGH);
      Serial.println("ON");
    } else if (serialData == '0') {
      digitalWrite(pin, LOW);
      Serial.println("OFF");
    }
  }
}
