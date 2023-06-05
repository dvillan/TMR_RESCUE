#include <Servo.h>
Servo myservo;
Servo myservoB;


//Definición de pines para servos Pan-Tilt
int servoV = 10;//PAN
int servoH = 11;//TILT

int deltaAngulo = 5;

int AngleValue = 0;
int AngleValueB = 0;

int desiredAngleValue = 0;
int desiredAngleValueB = 0;
int desiredAngleValue_reverse = 0;
int desiredAngleValueB_reverse = 0;

bool RightJoystickHorizontal = false;
bool RightJoystickVertical = false;
bool LeftJoystickVertical = false;
bool LeftJoystickHorizontal = false;

unsigned long previousMillis = 0;
const long interval = 100;

//Definición de pines Receptor
#define CH1 A8//A8
#define CH2 A9//A9
#define CH3 A10//A10
#define CH4 A11//A11
#define CH5 A12//A12

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup() {
  Serial.begin(115200);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  myservo.attach(servoH);//PAN
  myservoB.attach(servoV);//TILT
}

int ch1Value, ch3Value;

void loop() {
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, 0);

  desiredAngleValue = map(ch1Value, 10, 100, 90, 180); //Der
  desiredAngleValue_reverse = map(ch1Value, -10, -100, 90, 0);
  desiredAngleValueB = map(ch3Value, 10, 100, 90, 120); //Izq3
  desiredAngleValueB_reverse = map(ch3Value, -10, -100, 90, 0);//90, 45

  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" Ch3: ");
  Serial.print(ch3Value);
  delay(500);

  //Control camara Tilt
  if (ch3Value > 10) {
    LeftJoystickHorizontal = true;
    if (AngleValueB < desiredAngleValueB) {
      AngleValueB += deltaAngulo;
      myservoB.write(AngleValueB);
      Serial.print("Angle Value ");
      Serial.println(AngleValueB);
      Serial.println("MOVING CAMERA TILT");
      delay(10);
    }
  }
  else if (ch3Value < -10) {
    LeftJoystickHorizontal = true;
    if (AngleValueB > desiredAngleValueB_reverse) {
      AngleValueB -= deltaAngulo;
      myservoB.write(AngleValueB);
      Serial.print("Angle Value ");
      Serial.println(AngleValueB);
      Serial.println("MOVING CAMERA TILT");
      delay(10);
    }
  }

  else {
    LeftJoystickHorizontal = false;
  }


  if (LeftJoystickHorizontal != true) {
    if (AngleValueB > 90) {
      AngleValueB -= deltaAngulo;
      Serial.print(AngleValueB);
      Serial.print("Angle Value ");
      Serial.println(AngleValueB);
      Serial.println("MOVING CAMERA PAN");
    }
    else if (AngleValueB < 90) {
      AngleValueB += deltaAngulo;
      Serial.print(AngleValueB);
      Serial.print("Angle Value ");
      Serial.println(AngleValueB);
      Serial.println("MOVING CAMERA PAN");
    }
    else {
      AngleValueB = 90;
      Serial.print(AngleValueB);
      Serial.print("Angle Value ");
      Serial.println(AngleValueB);
      Serial.println("NEUTRAL ANGLE PAN");
    }
    delay(10);
    myservoB.write(AngleValueB);
  }

  delay(10);

  //Control PAN
  if (ch1Value > 10) {
    LeftJoystickHorizontal = true;
    if (AngleValue < desiredAngleValue) {
      AngleValue += deltaAngulo;
      myservo.write(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("MOVING CAMERA TILT");
      delay(10);
    }
  }
  else if (ch1Value < -10) {
    LeftJoystickHorizontal = true;
    if (AngleValue > desiredAngleValue_reverse) {
      AngleValue -= deltaAngulo;
      myservo.write(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("MOVING CAMERA TILT");
      delay(10);
    }
  }

  else {
    LeftJoystickHorizontal = false;
  }


  if (LeftJoystickHorizontal != true) {
    if (AngleValue > 90) {
      AngleValue -= deltaAngulo;
      Serial.print(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("MOVING CAMERA PAN");
    }
    else if (AngleValue < 90) {
      AngleValue += deltaAngulo;
      Serial.print(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("MOVING CAMERA PAN");
    }
    else {
      AngleValue = 90;
      Serial.print(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("NEUTRAL ANGLE PAN");
    }
    delay(10);
    myservo.write(AngleValue);
  }

  delay(10);
}