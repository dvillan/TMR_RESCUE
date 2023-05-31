#include <ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Twist.h>
#include<geometry_msgs/Vector3.h>
#include<std_msgs/Int32.h>


geometry_msgs::Vector3 data;
ros::Publisher pos("pos", &data);
ros::NodeHandle nh;


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

//Pines canales encoders
int canalAdf = 37;
int canalBdf = 39;
int canalAif = 41;
int canalBif = 43;
int canalAdb = 45;
int canalBdb = 47;
int canalAib = 49;
int canalBib = 51;

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

//velocidad rpm
double vel_rpmdf = 0;
double vel_rpmif = 0;
double vel_rpmdb = 0;
double vel_rpmib = 0;

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

void setup() {
  //Pines de interrupcion
  attachInterrupt(digitalPinToInterrupt(canalAdf), encoderdf, RISING);
  attachInterrupt(digitalPinToInterrupt(canalAif), encoderif, RISING);
  attachInterrupt(digitalPinToInterrupt(canalAdb), encoderdb, RISING);
  attachInterrupt(digitalPinToInterrupt(canalAib), encoderib, RISING);

  nh.initNode();
  nh.advertise(pos);

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
    vel_rpmdf = ((pos_actualdf - pos_antdf)60.00) / (360(dt) / 1000000.00); // rpm
    vel_rpmif = ((pos_actualif - pos_antif)60.00) / (360(dt) / 1000000.00); // rpm
    vel_rpmdb = ((pos_actualdb - pos_antdb)60.00) / (360(dt) / 1000000.00); // rpm
    vel_rpmib = ((pos_actualib - pos_antib)60.00) / (360(dt) / 1000000.00); // rpm

    //velocidad en m/s
    veldf = vel_rpmdf * pi * d_r / 60; //m/s
    velif = vel_rpmif * pi * d_r / 60; //m/s
    veldb = vel_rpmdb * pi * d_r / 60; //m/s
    velib = vel_rpmib * pi * d_r / 60; //m/s

    V = (veldf + velif + veldb + velib) / 4;

    //Serial.println(vel_rpm);

    pos_antdf = pos_actualdf;
    pos_antif = pos_actualif;
    pos_antdb = pos_actualdb;
    pos_antib = pos_actualib;

    data.x = V; //velocidad lineal
    data.y = 0; //angulo llanta derecha
    data.z = 0; //angulo llanta izquierda
    pos.publish(&data);
    t_ant = t_actual;
    nh.spinOnce();

  }


}