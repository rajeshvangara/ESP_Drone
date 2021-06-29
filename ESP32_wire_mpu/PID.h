//#include "imu.h"
class pid{
  
  public:
  float pid_error;
  float pid_error_prev;
  const float kp = 1.6;
  const float ki = 0.002845;
  const float kd = 0.9733;
  const float kd1 = 0.961;
  float pid_i;
  float pid_p;
  float pid_d;
  int pid_output_pitch;
 

  int pid_max = 100;

  void pid_controller(float current_angle, int output_angle, long double elapsedtime){
    pid_error = current_angle - output_angle;
    if ( pid_error < 3 && pid_error >  -3){
    pid_i += ki*pid_error;
    pid_d = kd1*((pid_error - pid_error_prev)/elapsedtime);
    //pid_d = kd1*((pid_error - pid_error_prev)/elapsedtime);
    //pid_output_pitch = kp1*pid_error + pid_i + kd1*((pid_error - pid_error_prev)/elapsedtime);
    }
    else  { 
      pid_i = pid_i;
      pid_d = kd*((pid_error - pid_error_prev)/elapsedtime);
      
    //pid_output_pitch = kp*pid_error + pid_i + kd*((pid_error - pid_error_prev)/elapsedtime);      
    }
//    pid_d = kd*((pid_error - pid_error_prev)/elapsedtime);
    pid_p = kp*pid_error;
    //pid_d = kd*((pid_error - pid_error_prev)/elapsedtime);
     
    pid_output_pitch = pid_p + pid_d + pid_i;
    
    if (pid_output_pitch > pid_max) pid_output_pitch = pid_max;
    else if(pid_output_pitch < pid_max*-1) pid_output_pitch = pid_max* -1;
    
//    pid_error_prev = pid_error;
    
    Serial.print(pid_error);Serial.print(" , ");
    Serial.print(pid_p), Serial.print(" , ");
    Serial.print(pid_d), Serial.print(" , ");
    Serial.println(pid_i);
    pid_error_prev = pid_error;    
  }
};
pid pid;
