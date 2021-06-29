#include <ESP32Servo.h>
class bldc{

  private:

  public:
  Servo bldc1;
  Servo bldc2;
   
  void bldc_setup(){
      ESP32PWM::allocateTimer(0);
      ESP32PWM::allocateTimer(1);
      ESP32PWM::allocateTimer(2);
      ESP32PWM::allocateTimer(3);

      bldc1.setPeriodHertz(250);
      bldc2.setPeriodHertz(250);
      bldc1.attach(12, 1000, 2000);
      bldc2.attach(19, 1000, 2000);
  }
 void bldc_write(int d1, int d2){
  
  bldc1.writeMicroseconds(1000 + d1);
  bldc2.writeMicroseconds(1000 + d2);  
 }
 
};
bldc bldc;
