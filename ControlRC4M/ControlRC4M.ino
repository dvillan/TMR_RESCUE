#define CH1 12
#define CH2 7
#define CH3 6
#define CH4 9
#define CH5 10

int Incremento = 5;

int ch1Value, ch2Value, ch3Value, ch4Value;
bool ch5Value;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

bool redSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

int pwmMotorFL = 2;
int pwmMotorFR = 3;
int pwmMotorBR = 4;
int pwmMotorBL = 5;

int pinDirFL = 48;
int pinDirFR = 46;
int pinDirBR = 44;
int pinDirBL = 42;

int pinBreak = 50;
int pwmValue = 0;
int desiredValue = 0;
int desiredValue_reverse =0;
bool isPressingUp = false;
unsigned long previousMillis = 0;
const long interval = 100;

void setup() {
  
  pinMode(pwmMotorFL, OUTPUT);
  pinMode(pwmMotorFR, OUTPUT);
  pinMode(pwmMotorBR, OUTPUT);
  pinMode(pwmMotorBL, OUTPUT);
  pinMode(pinDirFL, OUTPUT);
  pinMode(pinDirFR, OUTPUT);
  pinMode(pinDirBL, OUTPUT);
  pinMode(pinDirBR, OUTPUT);
  pinMode(pinBreak, OUTPUT);
  Serial.begin(115200);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
}

void loop() {
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = redSwitch(CH5, false);

//  Serial.print("ch1Value: ");
//  Serial.print(ch1Value);
//  Serial.print(" | ch2Value: ");
//  Serial.print(ch2Value);
//  Serial.print(" | ch3Value: ");
//  Serial.print(ch3Value);
//  Serial.print(" | ch4Value: ");
//  Serial.print(ch4Value);
//  Serial.print(" | ch5Value: ");
//  Serial.println(ch5Value);

    desiredValue_reverse = map(ch4Value, 10, 100, 0, 255);
    desiredValue = map(ch4Value, -10, -100, 0, 255);
  
  if (ch4Value < -10) {
    isPressingUp = true;
    digitalWrite(pinDirFL, HIGH);
    digitalWrite(pinDirFR, LOW);
    digitalWrite(pinDirBL, LOW);
    digitalWrite(pinDirBR, HIGH);
    digitalWrite(pinBreak, LOW);
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
  else if (ch4Value > 10) {
    isPressingUp = true;
    digitalWrite(pinDirFL, LOW);
    digitalWrite(pinDirFR, HIGH);
    digitalWrite(pinDirBL, HIGH);
    digitalWrite(pinDirBR, LOW);
    digitalWrite(pinBreak, LOW);
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
    isPressingUp = false;
//    digitalWrite(pinBreak, HIGH);
//    Serial.println("STOPPED");
  }

  if (isPressingUp != true) {
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
  if (pwmValue == 0){
    digitalWrite(pinBreak, HIGH);
    Serial.println("STOPPED");
  }
}
  }

  delay(10);
}
