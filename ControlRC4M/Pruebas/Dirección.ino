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
int BS4 = 6;//2 Adelante izq
int BS3 = 7;//3 Adelante der
int BS2 = 8;//4 Atrás der
int BS1 = 9;//5 Atrás izq

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

int pwmValue = 0;

int AngleValueBS4 = 1680;
int AngleValueBS3 = 1550;
int AngleValueBS2 = 1475;
int AngleValueBS1 = 1675;

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

  desiredBS4Angle = map(ch4Value, -100, 100, 1500, 1900);//1200 --> 0° , 1750 --> 180°, 1680 --> 90°
  desiredBS3Angle = map(ch4Value, -100, 100, 1400, 1775);//1310 --> 0° , 2000 --> 180°, 1550 --> 90°
  desiredBS2Angle = map(ch4Value, -100, 100, 1135, 1735);//1300 --> 0° , 1700 --> 180°, 1475 --> 90°
  desiredBS1Angle = map(ch4Value, -100, 100, 1500, 1850);//1230 --> 0° , 1830 --> 180°, 1675 --> 90°
  /*Set 90°
    AngleValueBS4 = 1670;//Atrás der
    myservoBS4.writeMicroseconds(AngleValueBS4);

    AngleValueBS3 = 1460;//Atrás izq
    myservoBS3.writeMicroseconds(AngleValueBS3);*/

  //Motor Adelante izq
  if (ch4Value > 20) {
    LeftJoystickVertical = true;
    if (AngleValueBS2 < desiredBS2Angle) {
      if (AngleValueBS2 < 1275) {
        AngleValueBS2 = 1275;
      }
      else {
        AngleValueBS2 -= 10;
      }
      myservoBS2.writeMicroseconds(AngleValueBS2);
      Serial.println(AngleValueBS2);
      Serial.println(ch4Value);
      delay(10);

    }
  }
  else if (ch4Value < -20) {
    LeftJoystickVertical = true;
    if (AngleValueBS2 > desiredBS2Angle) {
      if (AngleValueBS2 > 1680) {
        AngleValueBS2 = 1680;
      }
      else {
        AngleValueBS2 += 10;
      }
      myservoBS2.writeMicroseconds(AngleValueBS2);
      Serial.println(AngleValueBS2);
      Serial.println(ch4Value);
      delay(10);
    }
  }
  else {
    LeftJoystickVertical = false;
    if (AngleValueBS2 > 1475) {
      AngleValueBS2 -= 20;
    }
    else if (AngleValueBS2 < 1475) {
      AngleValueBS2 += 20;
    }
    else {
      AngleValueBS2 = 1475;
    }
    delay(10);
    myservoBS2.writeMicroseconds(AngleValueBS2);
    //  Serial.println(AngleValueBS2);
  }

  //Motor Adelante der
  if (ch4Value > 20) {
    LeftJoystickVertical = true;
    if (AngleValueBS1 < desiredBS2Angle) {
      if (AngleValueBS1 < 1500) {
        AngleValueBS1 = 1500;
      }
      else {
        AngleValueBS1 -= 10;
      }
      myservoBS1.writeMicroseconds(AngleValueBS1);
      // Serial.println(AngleValueBS1);
      delay(10);
    }
  }
  else if (ch4Value < -20) {
    LeftJoystickVertical = true;
    if (AngleValueBS1 > desiredBS2Angle) {
      if (AngleValueBS1 > 1850) {
        AngleValueBS1 = 1850;
      }
      else {
        AngleValueBS1 += 10;
      }
      myservoBS1.writeMicroseconds(AngleValueBS1);
      // Serial.println(AngleValueBS1);
      delay(10);
    }
  }
  else {
    LeftJoystickVertical = false;
    if (AngleValueBS1 > 1675) {
      AngleValueBS1 -= 20;
    }
    else if (AngleValueBS1 < 1675) {
      AngleValueBS1 += 20;
    }
    else {
      AngleValueBS1 = 1675;
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
    if (AngleValueBS4 > 1680) {
      AngleValueBS4 -= 20;
    }
    else if (AngleValueBS4 < 1680) {
      AngleValueBS4 += 20;
    }
    else {
      AngleValueBS4 = 1680;
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