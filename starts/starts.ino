#include <MPU6050_tockn.h> //scl =A5 / sda =A4 /vcc =5v / grn =grn
#include <Servo.h>

int ledping =7;  //led pin
int ledpinr =6;

int buzzer  =5; // buzzer pin 

int servopin1 = 9;  // Servo pin
int servopin2 = 10;
int servopin3 = 11;
int servopin4 = 12;

Servo servo1;   // Servo object 
Servo servo2;
Servo servo3;
Servo servo4;

int pos = 0; //position

MPU6050 mpu6050(Wire);

long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  servo1.attach(servopin1);   //attach object to pin 
  servo2.attach(servopin2);
  servo3.attach(servopin3);
  servo4.attach(servopin4);

  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {

  digitalWrite(ledpinr, HIGH);
  digitalWrite(ledping, HIGH);
  digitalWrite(buzzer, HIGH);
  mpu6050.update();

  if(millis() - timer > 1000){
    
    
    Serial.print("angleX : ");            // print 
    Serial.print(mpu6050.getAngleX());
    Serial.print("  angleY : ");
    Serial.println(mpu6050.getAngleY());

    timer = millis();

  }
      
       //x-axis / roll
      
  if( mpu6050.getAngleX() == -1<0< 1){                  
   servo2.write(90);    //set to 90 degrees
    }
   servo2.write(90 - mpu6050.getAngleY()); //unstable angle
   
   if( mpu6050.getAngleX() == 0){
      servo1.write(90); //set to 90 degrees
    }
   servo1.write(90 + mpu6050.getAngleY()); //unstable angle

       //y-axis / pitch 
       
   if(mpu6050.getAngleY() == 0){        
    servo3.write(90);//set to 90 degrees
    }
    servo3.write(90 +mpu6050.getAngleX()); //unstable angle
    
   if(mpu6050.getAngleY() == 0){
    servo4.write(90); //set to 90 degrees
    }
    servo4.write(90 - mpu6050.getAngleX());//unstable angle
  
  }
