//#include <ros.h>
//#include <geometry_msgs/Vector3Stamped.h>
//#include <geometry_msgs/Twist.h>
//#include<geometry_msgs/Vector3.h>
//#include<std_msgs/Int32.h>


//geometry_msgs::Vector3 data;
//ros::Publisher pos("pos",&data);
//ros::NodeHandle nh;



#include <YetAnotherPcInt.h>


int pwmValue = 0;



//Definiciones de pines PWM Brushless
int pwmMotorFR = 5;//9 Motor 1 //Atrás -- > BR
int pwmMotorFL = 4;//8 Motor 2 //Adelante
int pwmMotorBL = 3;//7 Motor 3 //Adelante
int pwmMotorBR = 2;//6 Motor 4 //Atrás --> FR

//Definición de pines Dirección Brushless
int pinDirFR = 35;//A1 Motor 1
int pinDirFL = 31;//A3 Motor 2
int pinDirBL = 27;//A5 Motor 3
int pinDirBR = 23;//A7 Motor 4

//Definición de pines Break Brushless
int pinBreakFR = 37;//A0 Motor 1 Atras derecha
int pinBreakFL = 33;//A2 Motor 2
int pinBreakBL = 29;//A4 Motor 3
int pinBreakBR = 25; //A6 Motor 4


// i -> izquierda    f - > frontal
//d -> derecha        b - > trasera

//Variables fisicas
double pi = 3.1416;
double d_r = 0.254; //m
double tpulsos = 15; //depende el motor
double paso = (360 / tpulsos); //grados


//Pulsos encoders
volatile int pulsosdf = 0;
volatile int pulsosif = 0;
volatile int pulsosdb = 0;
volatile int pulsosib = 0;

//Pines canales encoders interrupciones
#define canalAdf A11 // adelante
#define canalBdf 43
#define canalAif A10 //Adelante FL
#define canalBif 39
#define canalAdb A9 //atrás BR
#define canalBdb 45
#define canalAib A8 //atrás
#define canalBib 41

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
double V = 0;
double w = 0;


//velocidad rpm
double vel_rpmdf = 0;
double vel_rpmif = 0;
double vel_rpmdb = 0;
double vel_rpmib = 0;

//Funciones de contador pulsos encoders
void encoderdf () {
  if (digitalRead(canalAdf) == digitalRead(canalBdf))
  {
    pulsosdf ++;
  }
  else
  {
    pulsosdf --;
  }
}

void encoderif () {
  if (digitalRead(canalAif) == digitalRead(canalBif))
  {
    pulsosif ++;
  }
  else
  {
    pulsosif --;
  }
}

void encoderdb () {
  if (digitalRead(canalAdb) == digitalRead(canalBdb))
  {
    pulsosdb ++;
  }
  else
  {
    pulsosdb --;
  }
}
void encoderib () {
  if (digitalRead(canalAib) == digitalRead(canalBib))
  {
    pulsosib --;
  }
  else
  {
    pulsosib ++;
  }
}

void setup() {
  Serial.begin(115200);

  //Pines de interrupcion
  pinMode(canalAdf, INPUT_PULLUP);
  PcInt::attachInterrupt(canalAdf, encoderdf, RISING);
  pinMode(canalAif, INPUT_PULLUP);
  PcInt::attachInterrupt(canalAif, encoderif, RISING);
  pinMode(canalAdb, INPUT_PULLUP);
  PcInt::attachInterrupt(canalAdb, encoderdb, RISING);
  pinMode(canalAib, INPUT_PULLUP);
  PcInt::attachInterrupt(canalAib, encoderib, RISING);


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

  //nh.initNode();
  //nh.advertise(pos);

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
    vel_rpmdf = ((pos_actualdf - pos_antdf) * 60.00) / (360 * (dt) / 1000000.00); // rpm
    vel_rpmif = ((pos_actualif - pos_antif) * 60.00) / (360 * (dt) / 1000000.00); // rpm
    vel_rpmdb = ((pos_actualdb - pos_antdb) * 60.00) / (360 * (dt) / 1000000.00); // rpm
    vel_rpmib = ((pos_actualib - pos_antib) * 60.00) / (360 * (dt) / 1000000.00); // rpm

    //velocidad en m/s
    veldf = vel_rpmdf * pi * d_r / 60; //m/s
    velif = vel_rpmif * pi * d_r / 60; //m/s
    veldb = vel_rpmdb * pi * d_r / 60; //m/s
    velib = vel_rpmib * pi * d_r / 60; //m/s

    V = (veldf + velif + veldb + velib) / 4;
    w = 0;

    Serial.print(vel_rpmdf);
    Serial.print(", ");
    Serial.print(vel_rpmif);
    Serial.print(", ");
    Serial.print(vel_rpmdb);
    Serial.print(", ");
    Serial.println(vel_rpmib);

    pos_antdf = pos_actualdf;
    pos_antif = pos_actualif;
    pos_antdb = pos_actualdb;
    pos_antib = pos_actualib;

    //data.x=V; //velocidad lineal
    //data.y= 0; //angulo llanta derecha
    //data.z= 0; //angulo llanta izquierda
    //pos.publish(&data);
    t_ant = t_actual;
    //nh.spinOnce();

  }

  pwmValue = 80;

  digitalWrite(pinDirFL, HIGH);
  digitalWrite(pinDirFR, LOW);
  digitalWrite(pinDirBL, HIGH);
  digitalWrite(pinDirBR, LOW);
  digitalWrite(pinBreakFR, LOW);
  digitalWrite(pinBreakFL, LOW);
  digitalWrite(pinBreakBR, LOW);
  digitalWrite(pinBreakBL, LOW);


  analogWrite(pwmMotorFL, pwmValue); //FL
  analogWrite(pwmMotorFR, pwmValue); //FR --> BR
  analogWrite(pwmMotorBL, pwmValue); //BL
  analogWrite(pwmMotorBR, pwmValue); //BR --> FR

}