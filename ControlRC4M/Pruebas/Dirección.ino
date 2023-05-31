#include <Servo.h>
Servo myservoBS4;
Servo myservoBS3;
Servo myservoBS2;
Servo myservoBS1;

//Definición de pines Receptor
#define CH1 A8//A8
#define CH2 A9//A9
#define CH3 A10//A10
#define CH4 A11//A11
#define CH5 A12//A12

//Definición de pines Servos Dirección
int BS4 = 6;//2 Adelante der
int BS3 = 7;//3 Adelante izq
int BS2 = 8;//4 Atrás izq
int BS1 = 9;//5 Atrás der

int Incremento = 5;
int deltaAngulo = 5;


int ch1Value, ch2Value, ch3Value, ch4Value;
bool ch5Value;

// Lee el número de un canal dado y lo convierte al rango proporcionado.
// Si el canal está desactivado, devuelve el valor por defecto.
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Leer el canal y devolver un valor booleano
bool redSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}


int AngleValueBS4 = 1680;
int AngleValueBS3 = 1470;
int AngleValueBS2 = 1700;
int AngleValueBS1 = 1550;

int desiredBS4Angle = 0;
int desiredBS3Angle = 0;
int desiredBS2Angle = 0;
int desiredBS1Angle = 0;


bool RightJoystickHorizontal = false;
bool RightJoystickVertical = false;
bool LeftJoystickVertical = false;
bool LeftJoystickHorizontal = false;


void setup() {
  Serial.begin(115200);
  myservoBS4.attach(BS4, 1000, 2000);
  myservoBS3.attach(BS3, 1000, 2000);
  myservoBS2.attach(BS2, 1000, 2000);
  myservoBS1.attach(BS1, 1000, 2000);

  pinMode(CH4, INPUT);
}

void loop() {
  ch4Value = readChannel(CH4, -100, 100, 0);//Derecha vertical

  desiredBS4Angle = map(ch4Value, -100, 100, 1200, 1750);//1200 --> 0° , 1750 --> 180°
  desiredBS3Angle = map(ch4Value, -100, 100, 1310, 2000);//1310 --> 0° , 2000 --> 180°
  desiredBS2Angle = map(ch4Value, -100, 100, 1360, 2000);//1360 --> 0° , 2000 --> 180°
  desiredBS1Angle = map(ch4Value, -100, 100, 1230, 1830);//1230 --> 0° , 1830 --> 180°

  //Motor Adelante izq
  if (ch4Value > 20) {
    LeftJoystickVertical = true;
    if (AngleValueBS2 < desiredBS2Angle) {
      AngleValueBS2 += 20;
      myservoBS2.writeMicroseconds(AngleValueBS2);
      // Serial.println(AngleValueBS2);
      delay(10);
    }
  }
  else if (ch4Value < -20) {
    LeftJoystickVertical = true;
    if (AngleValueBS2 > desiredBS2Angle) {
      AngleValueBS2 -= 20;
      myservoBS2.writeMicroseconds(AngleValueBS2);
      // Serial.println(AngleValueBS2);
      delay(10);
    }
  }
  else {
    LeftJoystickVertical = false;
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
    //  Serial.println(AngleValueBS2);
  }

  //Motor Adelante der
  if (ch4Value > 20) {
    LeftJoystickVertical = true;
    if (AngleValueBS1 < desiredBS1Angle) {
      AngleValueBS1 += 20;
      myservoBS1.writeMicroseconds(AngleValueBS1);
      // Serial.println(AngleValueBS1);
      delay(10);
    }
  }
  else if (ch4Value < -20) {
    LeftJoystickVertical = true;
    if (AngleValueBS1 > desiredBS1Angle) {
      AngleValueBS1 -= 20;
      myservoBS1.writeMicroseconds(AngleValueBS1);
      // Serial.println(AngleValueBS1);
      delay(10);
    }
  }
  else {
    LeftJoystickVertical = false;
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
    // Serial.println(AngleValueBS1);
  }


  //Motor Atras izq
  if (ch4Value > 20) {
    LeftJoystickVertical = true;
    if (AngleValueBS4 < desiredBS4Angle) {
      AngleValueBS4 += 20;
      myservoBS4.writeMicroseconds(AngleValueBS4);
      // Serial.println(AngleValueBS4);
      delay(10);
    }
  }
  else if (ch4Value < -20) {
    LeftJoystickVertical = true;
    if (AngleValueBS4 > desiredBS4Angle) {
      AngleValueBS4 -= 20;
      myservoBS4.writeMicroseconds(AngleValueBS4);
      // Serial.println(AngleValueBS4);
      delay(10);
    }
  }
  else {
    LeftJoystickVertical = false;
    if (AngleValueBS4 > 1700) {
      AngleValueBS4 -= 20;
    }
    else if (AngleValueBS4 < 1700) {
      AngleValueBS4 += 20;
    }
    else {
      AngleValueBS4 = 1700;
    }
    delay(10);
    myservoBS4.writeMicroseconds(AngleValueBS4);
    //Serial.println(AngleValueBS4);
  }

  //Motor Atras der
  if (ch4Value > 20) {
    LeftJoystickVertical = true;
    if (AngleValueBS3 < desiredBS3Angle) {
      AngleValueBS3 += 20;
      myservoBS3.writeMicroseconds(AngleValueBS3);
      // Serial.println(AngleValueBS3);
      delay(10);
    }
  }
  else if (ch4Value < -20) {
    LeftJoystickVertical = true;
    if (AngleValueBS3 > desiredBS3Angle) {
      AngleValueBS3 -= 20;
      myservoBS3.writeMicroseconds(AngleValueBS3);
      //Serial.println(AngleValueBS3);
      delay(10);
    }
  }
  else {
    LeftJoystickVertical = false;
    if (AngleValueBS3 > 1550) {
      AngleValueBS3 -= 20;
    }
    else if (AngleValueBS3 < 1550) {
      AngleValueBS3 += 20;
    }
    else {
      AngleValueBS3 = 1550;
    }
    delay(10);
    myservoBS3.writeMicroseconds(AngleValueBS3);
    //Serial.println(AngleValueBS3);
  }
}