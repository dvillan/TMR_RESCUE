#include <Servo.h>
//#include <ros.h>
//#include <geometry_msgs/Vector3Stamped.h>
//#include <geometry_msgs/Twist.h>
//#include<geometry_msgs/Vector3.h>
//#include<std_msgs/Int32.h>
//
//geometry_msgs::Vector3 data;
//ros::Publisher pos("pos", &data);
//ros::NodeHandle nh;

Servo myservo;
Servo myservoB;
Servo myservoBS4;
Servo myservoBS3;
Servo myservoBS2;
Servo myservoBS1;

//Definición de pines Receptor
#define CH1 A8
#define CH2 A9
#define CH3 A10
#define CH4 A11
#define CH5 A12

//Definiciones de pines PWM Brushless
int pwmMotorFR = 5;//Motor 1 Atrás
int pwmMotorFL = 4;//Motor 2 Adelante
int pwmMotorBL = 3;//Motor 3 Adelante
int pwmMotorBR = 2;//Motor 4 Atrás

//Definición de pines Servos Dirección
int BS4 = 6;//Atrás der
int BS3 = 7;//Atrás izq
int BS2 = 8;//Adelante izq
int BS1 = 9;//Adelante der

// i -> izquierda    f - > frontal
//d -> derecha        b - > trasera

//Pines canales encoders
int canalAdf = 37;
int canalBdf = 39;
int canalAif = 41;
int canalBif = 43;
int canalAdb = 45;
int canalBdb = 47;
int canalAib = 49;
int canalBib = 51;

//Definición de pines Dirección Brushless
int pinDirFR = 36;//Motor 1
int pinDirFL = 32;//Motor 2
int pinDirBL = 28;//Motor 3
int pinDirBR = 24;//Motor 4

//Definición de pines Break Brushless
int pinBreakFR = 34;//Motor 1
int pinBreakFL = 30;//Motor 2
int pinBreakBL = 26;//Motor 3
int pinBreakBR = 22;//Motor 4

//Definición de pines para servos Pan-Tilt
int servoH = 10;//PAN
int servoV = 11;//TILT

int Incremento = 5;
int deltaAngulo = 5;

int pwmValue = 0;

//Variables servos camara
int AngleValue = 0;
int AngleValueB = 0;

//Definición 0° dirección servos
int AngleValueBS4 = 1680;
int AngleValueBS3 = 1470;
int AngleValueBS2 = 1700;
int AngleValueBS1 = 1550;

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

//Variables fisicas
double pi = 3.1416;
double d_r = 0.254; //m
double tpulsos = 15; //depende el motor
double paso = (360 / tpulsos); //grados

//Medidas del robot en m
double p_r = 0.79756; //perimetro llantas
double Lr = 0.17225; // Longitud desde el COG hacia atrás (centro de gravedad)
double Lf = 0.17225; // Longitud desde el COG hasta la parte delantera
double W = 0.43; //Ancho del robot

//Pulsos encoders
volatile int pulsosdf = 0;
volatile int pulsosif = 0;
volatile int pulsosdb = 0;
volatile int pulsosib = 0;

//Posicion actual y anterior llanta en grados
double pos_actualdf = 0;
double pos_antdf = 0;
double pos_actualif = 0;
double pos_antif = 0;
double pos_actualdb = 0;
double pos_antdb = 0;
double pos_actualib = 0;
double pos_antib = 0;


//Tiempo
double dt = 0;
double t_ant = 0;
double t_actual = 0;

//velocidades lineales
double veldf = 0;
double velif = 0;
double veldb = 0;
double velib = 0;
double Va = 0;
double wa = 0;

//velocidad rpm
double vel_rpmdf = 0;
double vel_rpmif = 0;
double vel_rpmdb = 0;
double vel_rpmib = 0;

//Remap ángulos
double AngleValueBS1_new = 0;
double AngleValueBS2_new = 0;
double AngleValueBS3_new = 0;
double AngleValueBS4_new = 0;

//Calculo velocidad ángular de cada rueda
double v1 = 0;
double v2 = 0;
double v3 = 0;
double v4 = 0;


int ch1Value, ch2Value, ch3Value, ch4Value;
bool ch5Value;

//Leer canales del control
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

//Leer switch del control
bool redSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup() {
  Serial.begin(115200);
  //Pines de interrupcion
  attachInterrupt(digitalPinToInterrupt(canalAdf), encoderdf, RISING);
  attachInterrupt(digitalPinToInterrupt(canalAif), encoderif, RISING);
  attachInterrupt(digitalPinToInterrupt(canalAdb), encoderdb, RISING);
  attachInterrupt(digitalPinToInterrupt(canalAib), encoderib, RISING);

  //  nh.initNode();
  //  nh.advertise(pos);

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
  t_actual = micros();
  dt = (t_actual - t_ant);
  if (dt >= 500000)
  {
    //Posicion actual en grados
    pos_actualdf = pulsosdf * paso;
    pos_actualif = pulsosif * paso;
    pos_actualdb = pulsosdb * paso;
    pos_actualib = pulsosib * paso;

    //velocidad rpm
    vel_rpmdf = ((pos_actualdf - pos_antdf)*60.00) / (360*(dt) / 1000000.00); // rpm
    vel_rpmif = ((pos_actualif - pos_antif)*60.00) / (360*(dt) / 1000000.00); // rpm
    vel_rpmdb = ((pos_actualdb - pos_antdb)*60.00) / (360*(dt) / 1000000.00); // rpm
    vel_rpmib = ((pos_actualib - pos_antib)*60.00) / (360*(dt) / 1000000.00); // rpm

    //velocidad en m/s
    veldf = vel_rpmdf * pi * d_r / 60; //m/s
    velif = vel_rpmif * pi * d_r / 60; //m/s
    veldb = vel_rpmdb * pi * d_r / 60; //m/s
    velib = vel_rpmib * pi * d_r / 60; //m/s

    //Va = (veldf + velif + veldb + velib) / 4;

    //Conversión ángulos
    AngleValueBS1_new = (0.18*AngleValueBS1)-180;
    AngleValueBS2_new = (0.18*AngleValueBS2)-180;
    AngleValueBS3_new = (0.18*AngleValueBS3)-180;
    AngleValueBS4_new = (0.18*AngleValueBS4)-180;

    //Calculo velocidad lineal
    Va = 1/4*(velif*cos(AngleValueBS1_new) + veldf*cos(AngleValueBS2_new) + veldb*cos(AngleValueBS3_new) + velib*cos(AngleValueBS4_new));//Velocidad lineal

    //Calculo velocidad angular
    v1 = velif*(((Lf*sin(AngleValueBS1_new))-((W/2)*cos(AngleValueBS1_new)))/(pow(Lf,2)+ pow(W/2,2)));
    v2 = veldf*(((Lf*sin(AngleValueBS2_new))+((W/2)*cos(AngleValueBS2_new)))/(pow(Lf,2)+ pow(W/2,2)));
    v2 = veldb*(((-Lr*sin(AngleValueBS3_new))+((W/2)*cos(AngleValueBS3_new)))/(pow(Lr,2)+ pow(W/2,2)));
    v2 = velib*(((-Lr*sin(AngleValueBS4_new))-((W/2)*cos(AngleValueBS4_new)))/(pow(Lr,2)+ pow(W/2,2)));
    wa = 1/4 * (v1 + v2 + v3 + v4); //Velocidad angular

    //Serial.println(vel_rpm);

    pos_antdf = pos_actualdf;
    pos_antif = pos_actualif;
    pos_antdb = pos_actualdb;
    pos_antib = pos_actualib;

    //    data.x = V; //velocidad lineal
    //    data.y = 0; //angulo llanta derecha
    //    data.z = 0; //angulo llanta izquierda
    //    pos.publish(&data);
    //    t_ant = t_actual;
    //    nh.spinOnce();

    ch1Value = readChannel(CH1, -100, 100, 0);
    ch2Value = readChannel(CH2, -100, 100, -100);
    ch3Value = readChannel(CH3, -100, 100, 0);
    ch4Value = readChannel(CH4, -100, 100, 0);
    //ch5Value = readChannel(CH5, -100, 100, 0);//
    ch5Value = redSwitch(CH5, false);

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
      //    digitalWrite(pinBreak, HIGH);
      //    Serial.println("STOPPED");
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


}

//Funciones de contador pulsos encoders
void encoderdf () {
  if (digitalRead(canalAdf) == digitalRead(canalBdf))
  { pulsosdf ++;
  }
  else
  { pulsosdf --;
  }
}

void encoderif () {
  if (digitalRead(canalAif) == digitalRead(canalBif))
  { pulsosif ++;
  }
  else
  { pulsosif --;
  }
}

void encoderdb () {
  if (digitalRead(canalAdb) == digitalRead(canalBdb))
  { pulsosdb ++;
  }
  else
  { pulsosdb --;
  }
}
void encoderib () {
  if (digitalRead(canalAib) == digitalRead(canalBib))
  { pulsosib ++;
  }
  else
  { pulsosib --;
  }
}
