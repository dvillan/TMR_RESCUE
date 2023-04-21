int val1;
int val2;

void setup(){
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()>=2){
    val1=Serial.read();
    val2=Serial.read();
    int intval1= int(val1);
    int intval2=int(val2);
    Serial.println(intval1 + 5);
    Serial.println(intval2 + 3);
  }
}
