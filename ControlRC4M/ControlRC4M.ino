#include <Servo.h>
Servo myservo;
Servo myservoB;
Servo myservoBS4;
Servo myservoBS3;
Servo myservoBS2;
Servo myservoBS1;

#define CH1 A8//A8
#define CH2 A9//A9
#define CH3 A10//A10
#define CH4 A11//A11
#define CH5 A12//A12

int Incremento = 5;
int deltaAngulo = 5;

int ch1Value, ch2Value, ch3Value, ch4Value, ch5Value;
//bool ch5Value;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

bool redSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
int pwmMotorFR = 5;//9 Motor 1 //Atrás
int pwmMotorFL = 4;//8 Motor 2 //Adelante
int pwmMotorBL = 3;//7 Motor 3 //Adelante
int pwmMotorBR = 2;//6 Motor 4 //Atrás

int BS4 = 6;//2 Atrás der
int BS3 = 7;//3 Atrás izq
int BS2 = 8;//4 Adelante izq
int BS1 = 9;//5 Adelante der

int pinDirFR = 36;//A1 Motor 1
int pinDirFL = 32;//A3 Motor 2
int pinDirBL = 28;//A5 Motor 3
int pinDirBR = 24;//A7 Motor 4

int pinBreakFR = 34;//A0 Motor 1 
int pinBreakFL = 30;//A2 Motor 2
int pinBreakBL = 26;//A4 Motor 3
int pinBreakBR = 22;//A6 Motor 4

int servoH = 10;//PAN
int servoV = 11;//TILT          

int pwmValue = 0;
int AngleValue = 0;
int AngleValueB = 0;
int AngleValueBS4 = 1680;
int AngleValueBS3 = 1470;
int AngleValueBS2 = 1700;//1570 //1660
int AngleValueBS1 = 1550;//1545 //1600

int desiredAngleValue = 0;
int desiredAngleValueB = 0;
int desiredAngleValue_reverse = 0;
int desiredAngleValueB_reverse = 0;
int desiredBS4Angle = 0;
int desiredBS3Angle = 0;
int desiredBS2Angle = 0;
int desiredBS1Angle = 0;

int desiredValue = 0;
int desiredValue_reverse = 0;

bool RightJoystickHorizontal = false;
bool RightJoystickVertical = false;
bool LeftJoystickVertical = false;
bool LeftJoystickHorizontal = false;

unsigned long previousMillis = 0;
const long interval = 100;

void setup() {
  Serial.begin(115200);
  myservoBS4.attach(BS4, 1000, 2000);
  myservoBS3.attach(BS3, 1000, 2000);
  myservoBS2.attach(BS2, 1000, 2000);
  myservoBS1.attach(BS1, 1000, 2000);
  pinMode(pwmMotorFL, OUTPUT);
  pinMode(pwmMotorFR, OUTPUT);
  pinMode(pwmMotorBR, OUTPUT);
  pinMode(pwmMotorBL, OUTPUT);
  pinMode(pinDirFL, OUTPUT);
  pinMode(pinDirFR, OUTPUT);
  pinMode(pinDirBL, OUTPUT);
  pinMode(pinDirBR, OUTPUT);
  pinMode(pinBreakFR, OUTPUT);
  pinMode(pinBreakFL, OUTPUT);
  pinMode(pinBreakBR, OUTPUT);
  pinMode(pinBreakBL, OUTPUT);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  myservo.attach(servoH);//PAN
  myservoB.attach(servoV);//TILT
}

void loop() {
  //ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, -100);//Izquierda horizontal
  ch3Value = readChannel(CH3, -100, 100, 0);//Izquierda vertical//100,-100
  ch4Value = readChannel(CH4, -100, 100, 0);//Derecha vertical
  ch5Value = readChannel(CH5, -100, 100, 0);//Derecha horizontal
  //ch5Value = redSwitch(CH5, false);

  desiredValue_reverse = map(ch2Value, 10, 100, 0, 125);
  desiredValue = map(ch2Value, -10, -100, 0, 100);
  desiredAngleValue = map(ch5Value, 10, 100, 90, 180); //Der
  desiredAngleValue_reverse = map(ch5Value, -10, -100, 90, 0);
  desiredAngleValueB = map(ch3Value, 10, 100, 90, 120); //Izq3
  desiredAngleValueB_reverse = map(ch3Value, -10, -100, 90, 0);//90, 45
  desiredBS4Angle = map(ch4Value, -100, 100, 1200, 1750);//2
  desiredBS3Angle = map(ch4Value, -100, 100, 1310, 2000);
  desiredBS2Angle = map(ch4Value, -100, 100, 1360, 2000);//1290,1845 //1380,1935+40
  desiredBS1Angle = map(ch4Value, -100, 100, 1230, 1830);//1270,1815 //1325,1870-20
  
  AngleValueBS4 = 1670;//Atrás der
  myservoBS4.writeMicroseconds(AngleValueBS4);

  AngleValueBS3 = 1460;//Atrás izq
  myservoBS3.writeMicroseconds(AngleValueBS3);
  
  //Motor Adelante izq
  if (ch4Value > 20) {
    LeftJoystickVertical = true;
    if (AngleValueBS2 < desiredBS2Angle) {
      AngleValueBS2 += 20;
      myservoBS2.writeMicroseconds(AngleValueBS2);
      Serial.println(AngleValueBS2);
      delay(10);
    }
  }
  else if (ch4Value < -20) {
    LeftJoystickVertical = true;
    if (AngleValueBS2 > desiredBS2Angle) {
      AngleValueBS2 -= 20;
      myservoBS2.writeMicroseconds(AngleValueBS2);
      Serial.println(AngleValueBS2);
      delay(10);
    }
  }
  else {
    LeftJoystickVertical = false;
  }

  if (LeftJoystickVertical != true) {
    if (AngleValueBS2 > 1700) {
      AngleValueBS2 -= 20;
    }
    else if (AngleValueBS2 < 1700) {
      AngleValueBS2 += 20;
    }
    else {
      AngleValueBS2 = 1700;
    }
    delay(10);
    myservoBS2.writeMicroseconds(AngleValueBS2);
    Serial.println(AngleValueBS2);
  }


  //Motor Adelante der
  if (ch4Value > 20) {
    LeftJoystickVertical = true;
    if (AngleValueBS1 < desiredBS1Angle) {
      AngleValueBS1 += 20;
      myservoBS1.writeMicroseconds(AngleValueBS1);
      Serial.println(AngleValueBS1);
      delay(10);
    }
  }
  else if (ch4Value < -20) {
    LeftJoystickVertical = true;
    if (AngleValueBS1 > desiredBS1Angle) {
      AngleValueBS1 -= 20;
      myservoBS1.writeMicroseconds(AngleValueBS1);
      Serial.println(AngleValueBS1);
      delay(10);
    }
  }
  else {
    LeftJoystickVertical = false;
  }

  if (LeftJoystickVertical != true) {
    if (AngleValueBS1 > 1550) {
      AngleValueBS1 -= 20;
    }
    else if (AngleValueBS1 < 1550) {
      AngleValueBS1 += 20;
    }
    else {
      AngleValueBS1 = 1550;
    }
    delay(10);
    myservoBS1.writeMicroseconds(AngleValueBS1);
    Serial.println(AngleValueBS1);
  }


  if (ch2Value < -10) {
    RightJoystickVertical = true;
    digitalWrite(pinDirFL, HIGH);
    digitalWrite(pinDirFR, LOW);
    digitalWrite(pinDirBL, HIGH);
    digitalWrite(pinDirBR, LOW);
    analogWrite(pinBreakFR, LOW);
    analogWrite(pinBreakFL, LOW);
    analogWrite(pinBreakBR, LOW);
    analogWrite(pinBreakBL, LOW);
    if (pwmValue < desiredValue) {
      pwmValue += Incremento;
      analogWrite(pwmMotorFL, pwmValue);
      analogWrite(pwmMotorFR, pwmValue);
      analogWrite(pwmMotorBL, pwmValue);
      analogWrite(pwmMotorBR, pwmValue);
      Serial.print("PWM value: ");
      Serial.println(pwmValue);
      Serial.println("MOVING");
      delay(10);
    }
  }
  else if (ch2Value > 10) {
    RightJoystickVertical = true;
    digitalWrite(pinDirFL, LOW);
    digitalWrite(pinDirFR, HIGH);
    digitalWrite(pinDirBL, LOW);
    digitalWrite(pinDirBR, HIGH);
    analogWrite(pinBreakFR, LOW);
    analogWrite(pinBreakFL, LOW);
    analogWrite(pinBreakBR, LOW);
    analogWrite(pinBreakBL, LOW);
    if (pwmValue < desiredValue_reverse) {
      pwmValue += Incremento;
      analogWrite(pwmMotorFL, pwmValue);
      analogWrite(pwmMotorFR, pwmValue);
      analogWrite(pwmMotorBL, pwmValue);
      analogWrite(pwmMotorBR, pwmValue);
      Serial.print("PWM value: ");
      Serial.println(pwmValue);
      Serial.println("MOVING");
      delay(10);
    }
  }
  else {
    RightJoystickVertical = false;
    
  }

  if (RightJoystickVertical != true) {
    if (pwmValue > 0) {
      if (pwmValue >= Incremento) {
        pwmValue -= Incremento;
      } else {
        pwmValue = 0;
      }
      delay(10);
      analogWrite(pwmMotorFL, pwmValue);
      analogWrite(pwmMotorFR, pwmValue);
      analogWrite(pwmMotorBL, pwmValue);
      analogWrite(pwmMotorBR, pwmValue);
      Serial.print("PWM value: ");
      Serial.println(pwmValue);
      if (pwmValue == 0) {
        analogWrite(pinBreakFR, HIGH);
        analogWrite(pinBreakFL, HIGH);
        analogWrite(pinBreakBR, HIGH);
        analogWrite(pinBreakBL, HIGH);
        Serial.println("STOPPED");
      }
    }
  }

  delay(10);


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

  //Control camara pan
  if (ch5Value > 10) {
    RightJoystickHorizontal = true;
    if (AngleValue < desiredAngleValue) {
      AngleValue += deltaAngulo;
      myservo.write(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("MOVING CAMERA");
      delay(10);
    }
  }
  else if (ch5Value < -10) {
    RightJoystickHorizontal = true;
    if (AngleValue > desiredAngleValue_reverse) {
      AngleValue -= deltaAngulo;
      myservo.write(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("MOVING CAMERA");
      delay(10);
    }
  }

  else {
    RightJoystickHorizontal = false;
  }


  if (RightJoystickHorizontal != true) {
    if (AngleValue > 90) {
      AngleValue -= deltaAngulo;
      Serial.print(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("MOVING CAMERA");
    }
    else if (AngleValue < 90) {
      AngleValue += deltaAngulo;
      Serial.print(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("MOVING CAMERA");
    }
    else {
      AngleValue = 90;
      Serial.print(AngleValue);
      Serial.print("Angle Value ");
      Serial.println(AngleValue);
      Serial.println("NEUTRAL ANGLE");
    }
    delay(10);
    myservo.write(AngleValue);
  }

  delay(10);
}