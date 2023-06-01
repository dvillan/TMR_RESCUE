//Definición de pines Receptor 
#define CH1 A8//A8
#define CH2 A9//A9
#define CH3 A10//A10
#define CH4 A11//A11
#define CH5 A12//A12

//Definiciones de pines PWM Brushless
int pwmMotorFR = 5;//9 Motor 1 //Atrás
int pwmMotorFL = 4;//8 Motor 2 //Adelante
int pwmMotorBL = 3;//7 Motor 3 //Adelante
int pwmMotorBR = 2;//6 Motor 4 //Atrás

//Definición de pines Dirección Brushless
int pinDirFR = 35;//A1 Motor 1
int pinDirFL = 31;//A3 Motor 2
int pinDirBL = 27;//A5 Motor 3
int pinDirBR = 23;//A7 Motor 4

//Definición de pines Break Brushless
int pinBreakFR = 37;//A0 Motor 1
int pinBreakFL = 33;//A2 Motor 2
int pinBreakBL = 29;//A4 Motor 3
int pinBreakBR = 25; //A6 Motor 4

int Incremento = 5;

int ch1Value, ch2Value, ch3Value, ch4Value, ch5Value;
//bool ch5Value;

//Función para leer canales del control
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

//Función para leer switch del control 
bool redSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
       
int pwmValue = 0;

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
}

void loop() {
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, -100);//Izquierda horizontal
  ch3Value = readChannel(CH3, -100, 100, 0);//Izquierda vertical//100,-100
  ch4Value = readChannel(CH4, -100, 100, 0);//Derecha vertical
  //ch5Value = readChannel(CH5, -100, 100, 0);//Derecha horizontal
  ch5Value = redSwitch(CH5, false);

  desiredValue_reverse = map(ch2Value, 10, 100, 0, 125);
  desiredValue = map(ch2Value, -10, -100, 0, 100);

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
}
