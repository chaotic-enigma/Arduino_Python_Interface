
int s2 = 7; // color sensor pin 7
int s3 = 8; // color sensor pin 8
int outPin = 4; // color sensor out to arduino pin 4

int trigPin = 9;
int echoPin = 10;

int rColorStrength; // red strength
int gColorStrength; // green strength
int bColorStrength; // blue strength

unsigned int pulseWidth; // measure color strength

float pingTime; // ping to travel till target from sensor
float targetDistance;
float speedOfSound = 776.5; // speed of sound in miles (default value)

void setup() {
  Serial.begin(115200);
  
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT); // pin to read the color

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  
  // read the RED component
  // s2 and s3 should be LOW
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  pulseWidth = pulseIn(outPin, LOW); // measure raw pulseWidth coming from the color sensor
  rColorStrength = pulseWidth/400.0 - 1; // normalize number in the range of 0 to 255
  rColorStrength = (255 - rColorStrength); // reverse --> large number means stronger

  // read the GREEN component
  // s2 and s3 should be HIGH
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  pulseWidth = pulseIn(outPin, LOW); // measure raw pulseWidth coming from the color sensor
  gColorStrength = pulseWidth/400. - 1; // normalize number in the range of 0 to 255
  gColorStrength = (255 - gColorStrength);
  //gColorStrength = gColorStrength + 2;

  // read the BLUE component
  // s2 - LOW and s3 - HIGH
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  pulseWidth = pulseIn(outPin, LOW); // measure raw pulseWidth coming from the color sensor
  bColorStrength = pulseWidth/400. - 1; // normalize number in the range of 0 to 255
  bColorStrength = (255 - bColorStrength); 

  // special validations
  // red - 255 
  if (rColorStrength > gColorStrength && gColorStrength > bColorStrength) {
    rColorStrength = 255;
    gColorStrength = gColorStrength / 2;
    bColorStrength = 0;
  }
  if (rColorStrength > bColorStrength && bColorStrength > gColorStrength) {
    rColorStrength = 255;
    bColorStrength = bColorStrength / 2;
    gColorStrength = 0;
  }

  // green - 255
  if (gColorStrength > rColorStrength && rColorStrength > bColorStrength) {
    gColorStrength = 255;
    rColorStrength = rColorStrength / 2;
    bColorStrength = 0;
  }
  if (gColorStrength > bColorStrength && bColorStrength > rColorStrength) {
    gColorStrength = 255;
    bColorStrength = bColorStrength / 2;
    rColorStrength = 0;
  }

  // blue - 255
  if (bColorStrength > rColorStrength && rColorStrength > gColorStrength) {
    bColorStrength = 255;
    rColorStrength = rColorStrength / 2;
    gColorStrength = 0;
  }
  if (bColorStrength > gColorStrength && gColorStrength > rColorStrength) {
    bColorStrength = 255;
    gColorStrength = gColorStrength / 2;
    rColorStrength = 0;
  }

  // measure distance to target through Ultra-Sonic sensor
  // MANIPULATION
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  pingTime = pulseIn(echoPin, HIGH);
  pingTime = pingTime / 1000000; // convert into seconds
  pingTime = pingTime / 3600; // convert into hours
  targetDistance = speedOfSound * pingTime; // distance in miles
  targetDistance = targetDistance / 2; //
  targetDistance = targetDistance * 63360; // convert miles into inches

  // print data -- (red, green, blue, distance)
  //Serial.print("(");
  Serial.print(rColorStrength);
  Serial.print(", ");
  Serial.print(gColorStrength);
  Serial.print(", ");
  Serial.print(bColorStrength);
  Serial.print(", ");
  Serial.println(targetDistance);

  delay(150);
}
