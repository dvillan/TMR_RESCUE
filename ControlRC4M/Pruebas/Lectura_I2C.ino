#include <Wire.h>
const int direccion = 0x5;

double Va = 0;
double wa = 0;
//Medidas del robot en m
double p_r = 0.79756; //perimetro llantas
double Lr = 0.17225; // Longitud desde el COG hacia atrás (centro de gravedad)
double Lf = 0.17225; // Longitud desde el COG hasta la parte delantera
double W = 0.43; //Ancho del robot

//Variables fisicas
double pi = 3.1416;
double d_r = 0.254; //m
double tpulsos = 15; //depende el motor
double paso = (360 / tpulsos); //grados

//Pulsos encoders
volatile int pulsosdf = 0;
volatile int pulsosif = 0;

//Pines canales encoders
int canalAdf = 2;
int canalBdf = 4;
int canalAif = 3;
int canalBif = 5;
//Posicion actual y anterior llanta en grados
double pos_actualdf=0; 
double pos_antdf = 0;
double pos_actualif=0;
double pos_antif = 0;

//Tiempo
double dt = 0;
double t_ant = 0;
double t_actual = 0;

//velocidades lineales
double veldf = 0;
double velif = 0;
//velocidad rpm
double vel_rpmdf = 0;
double vel_rpmif = 0;
double V = 0;
double w = 0;
double v1 = 0;
double v2 = 0;

//Funciones de contador pulsos encoders
void encoderdf () {
if (digitalRead(canalAdf) == digitalRead(canalBdf))
{pulsosdf ++;
}
else
{pulsosdf --;
}
}

void encoderif () {
if (digitalRead(canalAif) == digitalRead(canalBif))
{pulsosif ++;
}
else
{pulsosif --;
}
}

//dato recibido I2C
double angulo1;
double angulo2;
void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(canalAdf), encoderdf, RISING);
  attachInterrupt(digitalPinToInterrupt(canalAif), encoderif, RISING);
  Wire.begin(direccion);//Unimos este dispositivo al bus I2C como esclavO
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  t_actual = micros();
  dt = (t_actual - t_ant);
   if (dt>=500000)
  {
    //Posicion actual en grados
    pos_actualdf = pulsosdf*paso;
    pos_actualif = pulsosif*paso;


    //velocidad rpm 
    vel_rpmdf = ((pos_actualdf-pos_antdf)*60.00)/(360*(dt)/1000000.00); // rpm
    vel_rpmif = ((pos_actualif-pos_antif)*60.00)/(360*(dt)/1000000.00); // rpm
  

    //velocidad en m/s       
    veldf = vel_rpmdf*pi*d_r/60; //m/s
    velif = vel_rpmif*pi*d_r/60; //m/s
  
    
    Va = (velif * cos(angulo1) + veldf * cos(angulo2)) / 2; //Velocidad lineal
    v1 = velif * (((Lf * sin(angulo1)) - ((W / 2) * cos(angulo1))) / (pow(Lf, 2) + pow(W / 2, 2)));
    v2 = veldf * (((Lf * sin(angulo2)) + ((W / 2) * cos(angulo2))) / (pow(Lf, 2) + pow(W / 2, 2)));
    wa = (v1+v2)/2;
    

    pos_antdf = pos_actualdf;
    pos_antif = pos_actualif;

    t_ant = t_actual;
    Serial.print(Va);
    Serial.print(",");
    Serial.print(wa);
    Serial.print(",");
    Serial.println(angulo1);
  }
  
 
  }


void receiveEvent(int howMany) {
  if (Wire.available())
  {
    angulo1 = Wire.read();
    angulo2 = Wire.read();
    //Serial.println(angulo1);
    //Serial.println(angulo2);
  }
}
