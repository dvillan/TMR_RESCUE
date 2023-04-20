#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int posMIN = 20;//60 25
int posMAX = 65;//120 65
int posNEUTRO = 45;//85 50
void setup() {
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  myservo.write(25);
  Serial.begin(9600);
}

void loop() {
//  Serial.println("Conectando...");
//  delay(1000);
}


////LIBRARIES:
//#include <Servo.h> 
//
//Servo myservo;  //creamos un objeto servo 
//int angulo;
//
//void setup(){
//  myservo.attach(3);  // asignamos el pin 3 al servo.
//  Serial.begin(9600); // iniciamos el puerto serial
//}
//
// 
//void loop() { 
//  
//  angulo= 0;
//  myservo.write(angulo);
//  Serial.print("ángulo:  ");
//  Serial.println(angulo);
//  delay(2000);  
//
//  angulo= 90;
//  myservo.write(angulo);
//  Serial.print("ángulo:  ");
//  Serial.println(angulo);
//  delay(2000); 
//
//  angulo= 180;
//  myservo.write(angulo);
//  Serial.print("ángulo:  ");
//  Serial.println(angulo);
//  delay(2000);
//
//  angulo= 90;
//  myservo.write(angulo);
//  Serial.print("ángulo:  ");
//  Serial.println(angulo);
//  delay(2000);
//} 
