
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define BYTELENGTH 10
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVO_MIN_PULSE_WIDTH  100 // this is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX_PULSE_WIDTH  575 // this is the 'maximum' pulse length count (out of 4096)
#define SERVO_MAX_DEGREE 180

// our servo # counter
uint8_t servonum = 0;
int val;
int pulselen;
int IRSensor = 9; 
bool shouldWaitForSensor = true;
bool newDataAllowed = true;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pinMode(IRSensor, INPUT);
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates


  setServoPosition(4,28);// Initial position for servo 1 (adjust as needed)
  //Center = 10
  setServoPosition(8, 50);
  setServoPosition(7, 40);
  setServoPosition(15, 60);
  setServoPosition(12, 110);
  


 
}

void loop() {
    int sensorStatus = digitalRead(IRSensor);
    bool dataReceived = false;
    char data;
    while(sensorStatus == 0) {
      delay(3000);

      //setServoPosition(12, 60);
      //delay(500);
      setServoPosition(15, 200);
      delay(2000);
      setServoPosition(8, 40);
      delay(2000);
      setServoPosition(8, 5);
      delay(2000);

      setServoPosition(4, 40);
      delay(500);
      /*
      setServoPosition(4, 50);
      delay(500);
      setServoPosition(4, 60);
      delay(500);
      setServoPosition(4, 70);
      delay(500);
      setServoPosition(4, 80);
      delay(500);
      setServoPosition(4, 90);
      delay(500);
      setServoPosition(4, 100);
      delay(500);
      setServoPosition(4, 110);
      delay(500);
      *//*
      setServoPosition(4, 120);
      delay(500);
      setServoPosition(4, 130);
      delay(500);
      setServoPosition(4, 140);
      delay(500);
      setServoPosition(4, 150);
      delay(500);
      setServoPosition(4, 160);
      delay(500);
      setServoPosition(4, 170);
      delay(500);
      */
      setServoPosition(4, 180);
      delay(2000);

      setServoPosition(8,30);
      delay(2000);
      setServoPosition(15, 200);
      delay(2000);
      //setServoPosition(7,40);
      //delay(2000);

      if (Serial.available() > 0 && !dataReceived && newDataAllowed) 
      {
      data = Serial.read();
      switch (data) {
          case 'r':
              setServoPosition(4, 207);
              delay(2000);
              setServoPosition(8, 35);
              delay(2000);
              setServoPosition(15, 20);
              delay(2000);
              setServoPosition(8, 30);
              delay(2000);
              dataReceived = true;
              break;
          case 'p':
              setServoPosition(4, 195);
              delay(2000);
              setServoPosition(15, 20);
              delay(2000);
              dataReceived = true;
              break;
          case 'b':
              setServoPosition(4, 180);
              delay(2000);
              setServoPosition(15, 20);
              delay(2000);
              dataReceived = true;
              break;        
          case 'g':
              setServoPosition(4, 160);
              delay(2000); 
              setServoPosition(15, 20);
              delay(2000);        
              dataReceived = true;  
              break;
          case 'y':
              setServoPosition(4, 140);
              delay(2000); 
              setServoPosition(15, 20);
              delay(2000);        
              dataReceived = true;  
              break;

          default:
              setServoPosition(4, 180);
              delay(2000);  
              //setServoPosition(12, 20);
              //delay(2000);
              dataReceived = true;
              break;
      }
        while (Serial.available() > 0) {
          Serial.read();
        } 
      }
      setServoPosition(8, 5);
      delay(2000);

      setServoPosition(4, 140);
      delay(500);
      
      
      setServoPosition(4, 90);
      delay(500);
      
      setServoPosition(4, 40);
      delay(500);
      
      setServoPosition(4, 30);
      delay(500);
      setServoPosition(4,25);// Initial position for servo 1 (adjust as needed)
      delay(2000);
      setServoPosition(8, 50);
      delay(1000);

      
      setServoPosition(12, 110);
      delay(1000);
      setServoPosition(15, 60);
      delay(1000);
      data = 'x';
      dataReceived = true;
      newDataAllowed = true;
      break;
    }
  }

 //Function to set servo position
void setServoPosition(uint8_t servoNum, int degree) {
  // Convert degree to pulse width
  int pulseWidth = map(degree, 0, SERVO_MAX_DEGREE, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
  
  // Set PWM signal to the servo
  pwm.setPWM(servoNum, 0, pulseWidth);
}
  