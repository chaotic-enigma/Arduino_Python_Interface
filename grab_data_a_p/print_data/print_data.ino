
int count = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Python Arduino: ");
  Serial.print(count);
  Serial.println(" hoohoohoo!");
  count += 1;
  delay(1000);
}
