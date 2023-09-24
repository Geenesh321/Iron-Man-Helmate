#include <Servo.h>
Servo servo1;
Servo servo2;
int servoPin = 9;
int servoPin2 = 10;

int IRSensor = 8;

bool isOpened = false;
bool isBlue = true;
//bool isBlue = true;

int redLight = 6;
int blueLight = 7;

void setup() {
  Serial.begin(9600);
  
  servo1.attach(servoPin);
  servo2.attach(servoPin2);
  servo1.write(0);
  servo2.write(180);


  pinMode(IRSensor, INPUT);

  pinMode(redLight, OUTPUT);
  pinMode(blueLight, OUTPUT);
//  closeHelmet();
  digitalWrite(blueLight, HIGH);
 }

void loop() {
  int sensorStatus = digitalRead(IRSensor);
  if (sensorStatus == 0)
  {
    Serial.println("Motion Detected!");
  }
  else  {
    Serial.println("Motion Ended!");
    if (isOpened) {
      closeHelmet();
      delay(2000);
    } else {
      openHelmet();
      delay(2000);
    }
  }
}

void openHelmet() {
  Serial.println("Helmet Opened");
  digitalWrite(redLight, LOW);
  digitalWrite(blueLight, LOW);
  for(int i = 0; i <= 180; i += 1){
    servo1.write(i);
    servo2.write(180-i);
//    delay(5);
  }
  isOpened = true;
}

void closeHelmet() {
  Serial.println("Helmet Closed");
  for(int i = 180; i >= 0; i -= 1){
    servo1.write(i);
    servo2.write(180-i);
    delay(5);
  }
  delay(1500);
  if(isBlue){
    digitalWrite(blueLight, HIGH);
    digitalWrite(redLight, LOW);
  }
  else{
    digitalWrite(redLight, HIGH);
    digitalWrite(blueLight, LOW);
  }
  isOpened = false;
}
