#define echopin_s1 A2 // echo pin
#define triggerpin_s1 A3 // Trigger pin

#define echopin_s2 A0 // echo pin
#define triggerpin_s2 A1 // Trigger pin
int Light_A = 12;
int Light_B = 13;
int Light_C =11;
int Bulb1 = 0;
int Bulb2 = 0;
int Bulb3 = 0;
long dis_1 = 0;     
long dis_2 = 0;
int flag1 = 0; 
int flag2 = 0;
int person = 0; 
int sensorPin = A4; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor

void ultra_read(int pin_t,int pin_e,long &ultra_distance){
long time;
pinMode(pin_t,OUTPUT);
pinMode(pin_e,INPUT);
digitalWrite(pin_t,LOW);
delayMicroseconds(2);
digitalWrite(pin_t,HIGH);
delayMicroseconds(10);
time=pulseIn (pin_e,HIGH);
ultra_distance =  time / 29 / 2; 
}
//Lux
double Light (int RawADC0){
double Vout=RawADC0*0.0048828125;
//int lux=500/(10*((5-Vout)/Vout));//use this equation if the LDR is in the upper part of the divider
int lux=(2500/Vout-500)/10;
return lux;
}

void setup(){
Serial.begin(9600);// initialize serial communication at 4600 bits per second:
pinMode(sensorPin, INPUT);
pinMode(Light_A, OUTPUT);
pinMode(Light_B,OUTPUT);
pinMode(Light_C,OUTPUT); 
}

void loop()
{ 
ultra_read(triggerpin_s1,echopin_s1,dis_1);delay(10);// dis_1 is distance of found object less than 50cm from the sensor 1
ultra_read(triggerpin_s2,echopin_s2,dis_2);delay(10);//dis_2 is distance of found object less than 50cm from the sensor 2
sensorValue = int(Light(analogRead(A4))); // read the value from the sensor
delay(1000);
Serial.print("distance 1 is :");
Serial.println(dis_1);
Serial.print("distance 2 is :");
Serial.println(dis_2);   
if(dis_1<90 && flag1==0){flag1=1;
if(flag2==0){person = person+1;}
}

if(dis_2<90 && flag2==0){flag2=1;
if(flag1==0){person = person-1;}
}

if(dis_1>90 && dis_2>90 && flag1==1 && flag2==1){
flag1=0, flag2=0;
delay(1000); 
}


Serial.print("Person Inside Room: ");
Serial.println(person);
delay(1000);
Serial.print("Ldr value:");
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
/*Serial.println(flag1);
Serial.println(flag2);*/
if (Serial.available()){
int state=Serial.read();
Serial.println(state);

if (state == 48){
  if (Bulb1 == 1){
  Bulb1=0;
  digitalWrite(Light_A,LOW);
  Serial.println("Light_A OFF");
  }
}
if (state == 49){
  if (Bulb1 == 0){
  Bulb1=1;
  digitalWrite(Light_A,HIGH);
  Serial.println("Light_A ON");
  }
}
if (state == 50){
  if (Bulb2 == 1){
  Bulb2=0;
  digitalWrite(Light_B,LOW);
  Serial.println("Light_B OFF");
  }
}
if (state == 51){
  if (Bulb2 ==0 ){
  Bulb2=1;
  digitalWrite(Light_B,HIGH);
  Serial.println("Light_B ON");
  }
}
if (state == 52){
  if (Bulb3 == 1){
  Bulb3=0;
  digitalWrite(Light_C,LOW);
  Serial.println("Light_C OFF");
  }
}
if (state == 53){
  if (Bulb3 == 0){
  Bulb3=1;
  digitalWrite(Light_C,HIGH);
  Serial.println("Light_C ON");
  }
}
}
if (Bulb1 ==0)
{
if(person>0 && sensorValue < 150)
{
  digitalWrite(Light_A,HIGH);
  Serial.println("Need light-Switch on Light A");
}
else
{
  digitalWrite(Light_A,LOW);
  Serial.println("No need light");
}
}
}