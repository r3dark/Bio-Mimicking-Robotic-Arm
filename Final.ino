/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

int potpin0=0;  //Pot on analog 0
int potpin1=1;  //Pot on analog 1
int potpin2=2;  //Pot on analog 2
int potpin3=3;  //Pot on analog 3
int potpin6=6;  //Pot on analog 6


int val0;       //Val from Pot
int val1;
int val2;
int val3;
int val6;
int rval;


int adc0,adc1;    //Adc values;
int adc2,adc3;
int adc6,radc;


void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //yield();
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  /* // Drive each servo one at a time
  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(500);

  servonum ++;
  if (servonum > 7) servonum = 0;

  */
  val0 = analogRead(potpin0);       //Reads value from pot0
  val1 = analogRead(potpin1);       //Reads value from pot1
  val2 = analogRead(potpin2);       //Reads value from pot2
  val3 = analogRead(potpin3);       //Reads value from pot3
  val6 = analogRead(potpin6);       //Reads value from pot6

  if(val2<=240)
    adc2 = map(val2,140,240,160,273);
  else
    adc2=map(val2,240,970,276,590);
  
  adc0 = map(val0,100,840,160,590);    //maps pot value to pwm pulse length
  radc = map(val1,180,1000,160,590);
  adc1 = map(val1,180,1000,590,160);
//  adc2 = map(val2,140,970,160,590);
  adc3 = map(val3,130,900,160,590);    // servo in opposite dir
  adc6 = map(val6,40,140,295,160);     //claw 0 to 90 only and servo in opposite dir

//  Serial.println(val2);
//  Serial.println(" ");
//  Serial.println(adc2);
//  delay(150);
  pwm.setPWM(0 ,0, adc0);             //sends pwm to servo
  pwm.setPWM(1 ,0, adc1);
  pwm.setPWM(2 ,0, radc);
  pwm.setPWM(3 ,0, adc2);
  pwm.setPWM(4 ,0, adc3);
  pwm.setPWM(5 ,0, adc6);
}
