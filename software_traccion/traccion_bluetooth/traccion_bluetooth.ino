
int R_EN1 = 50;
int R_PWM1 = 11;
int L_EN1 = 51;
int L_PWM1 = 10;

int R_EN2 = 52;
int R_PWM2 = 8;
int L_EN2 = 53;
int L_PWM2 = 9;

int LED = 13;

char t;
int a = 0;
bool flag = 0;


void setup() {
  pinMode(LED, OUTPUT);
  // Right Motor
  pinMode(R_EN1, OUTPUT);
  pinMode(R_PWM1, OUTPUT);
  pinMode(L_EN1, OUTPUT);
  pinMode(L_PWM1, OUTPUT);
  // Left Motor
  pinMode(R_EN2, OUTPUT);
  pinMode(R_PWM2, OUTPUT);
  pinMode(L_EN2, OUTPUT);
  pinMode(L_PWM2, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(R_EN1, HIGH);
  digitalWrite(L_EN1, HIGH);
  digitalWrite(R_EN2, HIGH);
  digitalWrite(L_EN2, HIGH);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {
    t = Serial.read();
//    if (t == 'w') {
//      flag = !flag;
//    }
    if (flag == 0) {
      if (t == 'F') {
        digitalWrite(LED, LOW);
        analogWrite(R_PWM1, 255);
        analogWrite(L_PWM1, 0);
        analogWrite(R_PWM2, 0);
        analogWrite(L_PWM2, 0);
        
      }
      else if (t == 'B') {
        digitalWrite(LED, LOW);
        analogWrite(R_PWM1, 0);
        analogWrite(L_PWM1, 255);
        analogWrite(R_PWM2, 0);
        analogWrite(L_PWM2, 0);
        
      }
      else if (t == 'L') {
        digitalWrite(LED, LOW);
        analogWrite(R_PWM1, 0);
        analogWrite(L_PWM1, 0);
        analogWrite(R_PWM2, 255);
        analogWrite(L_PWM2, 0);
        
      }
      else if (t == 'R') {
        digitalWrite(LED, LOW);
        analogWrite(R_PWM1, 0);
        analogWrite(L_PWM1, 0);
        analogWrite(R_PWM2, 0);
        analogWrite(L_PWM2, 255);
        
      }
      else {
        digitalWrite(LED, HIGH);
        analogWrite(R_PWM1, 0);
        analogWrite(L_PWM1, 0);
        analogWrite(R_PWM2, 0);
        analogWrite(L_PWM2, 0);
        
      }
    }
    else if (flag == 1) {
      digitalWrite(LED, LOW);
      //      if (t == 'L') {
      //        digitalWrite(3, 1);
      //        digitalWrite(4, 0);
      //        analogWrite(2, 250);
      //
      //        digitalWrite(6, 1);
      //        digitalWrite(7, 0);
      //        analogWrite(5, 250);
      //        delay(10);
      //      }
      //      else if (t == 'R') {
      //        digitalWrite(3, 0);
      //        digitalWrite(4, 1);
      //        analogWrite(2, 250);
      //
      //        digitalWrite(6, 0);
      //        digitalWrite(7, 1);
      //        analogWrite(5, 250);
      //        delay(10);
      //      }
      //      else if (t == 'F') {
      //        digitalWrite(3, 1);
      //        digitalWrite(4, 0);
      //        analogWrite(2, 250);
      //
      //        digitalWrite(6, 0);
      //        digitalWrite(7, 1);
      //        analogWrite(5, 250);
      //        delay(10);
      //      }
      //      else if (t == 'B') {
      //        digitalWrite(3, 0);
      //        digitalWrite(4, 1);
      //        analogWrite(2, 250);
      //
      //        digitalWrite(6, 1);
      //        digitalWrite(7, 0);
      //        analogWrite(5, 250);
      //        delay(10);
      //      }
      //      else {
      //        digitalWrite(LED, HIGH);
      //        digitalWrite(3, 0);
      //        digitalWrite(4, 0);
      //        analogWrite(2, 0);
      //
      //        digitalWrite(6, 0);
      //        digitalWrite(7, 0);
      //        analogWrite(5, 0);
      //
      //        delay(10);
      //      }
    }

  }
}
