#include<Wire.h>
#include"imu.h"
#include "pwm.h"
#include "ble.h"
#include "PID.h"
//#include "pid_dps.h"


long double timeprev;
long double imu_timer;
long double elapsedtime;

void setup() {
  
 // put your setup code here, to run once:
Serial.begin(115200);
//ble.setup();
bldc.bldc_setup();
bldc.bldc_write(1000, 1000);

//###### IMU SETUP ######//
IMU.mpu_6050_setup(21,22, 1);

//###### ESC SETUP ######//
delay(2000); // optional
bldc.bldc_write(0,0);
pinMode(2, OUTPUT);
digitalWrite(2, HIGH);
delay(100);
digitalWrite(2, LOW);
delay(6000);
digitalWrite(2,HIGH);
delay(200);
digitalWrite(2,LOW);
//imu_timer = micros();

}

void loop() {
  // put your main code here, to run repeatedly:
timeprev = imu_timer;  // the previous time is stored before the actual time read
imu_timer = micros();  // actual time read
elapsedtime = (imu_timer - timeprev) / 1000000; 

IMU.mpu_read_data();
IMU.mpu_process(elapsedtime);
//IMU.serial_print();
//Serial.print(IMU.gyro_pitch);
//Serial.print(" , ");
if (isnan(IMU.angle_pitch_output)){
  
  bldc.bldc_write(0,0);
  digitalWrite(2, HIGH);
  //IMU.mpu_6050_setup(21,22,0);  
}
else{
pid.pid_controller(IMU.angle_pitch_output, 0, elapsedtime);

//ble.loop();

bldc.bldc_write(200 + pid.pid_output_pitch, 200 - pid.pid_output_pitch);
}
//Serial.print(" , ");
//Serial.println(micros()- imu_timer);
//while(micros() - imu_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
//  imu_timer = micros();
                                               //Reset the loop timer
}
