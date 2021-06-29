class MPU_6050{

  private:
  
  const int MPU_ADDR = 0x68;

  public:
  
//  int16_t Ax, Ay, Az, Tp, Gx, Gy, Gz;
int16_t gyro_x, gyro_y, gyro_z;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
int16_t acc_x, acc_y, acc_z, acc_total_vector;
int16_t Tp;
long acc_x_cal, acc_y_cal, acc_z_cal;
float angle_pitch, angle_roll, angle_yaw;
int angle_pitch_buffer, angle_roll_buffer;
boolean set_gyro_angles;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_output, angle_yaw_output;
float gyro_pitch;

  void mpu_6050_setup(int SDA, int SCL, int cal){
    Wire.begin(SDA,SCL,400000); // sda, scl, clock speed 
    Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
    Wire.write(0x6B);                                                    //Send the requested starting register
    Wire.write(0x00);                                                    //Set the requested starting register
    Wire.endTransmission(true);                                              //End the transmission
    //Configure the accelerometer (+/-8g)
    Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
    Wire.write(0x1C);                                                    //Send the requested starting register
    Wire.write(0x10);                                                    //Set the requested starting register
    Wire.endTransmission(true);                                              //End the transmission
    //Configure the gyro (500dps full scale)
    Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
    Wire.write(0x1B);                                                    //Send the requested starting register
    Wire.write(0x08);                                                    //Set the requested starting register
    Wire.endTransmission(true);
if ( cal == 1){
    Serial.print(" Gyro Calibration");
    
  for (int cal_int = 0; cal_int < 2000 ; cal_int ++){                  //Run this code 2000 times
    if(cal_int % 125 == 0)Serial.print(".");                              //Print a dot on the LCD every 125 readings
    mpu_read_data();                                             //Read the raw acc and gyro data from the MPU-6050
    gyro_x_cal += gyro_x;                                              //Add the gyro x-axis offset to the gyro_x_cal variable
    gyro_y_cal += gyro_y;                                              //Add the gyro y-axis offset to the gyro_y_cal variable
    gyro_z_cal += gyro_z;                                              //Add the gyro z-axis offset to the gyro_z_cal variable
    delay(3);                                                          //Delay 3us to simulate the 250Hz program loop
  }
  gyro_x_cal /= 2000;                                                  //Divide the gyro_x_cal variable by 2000 to get the avarage offset
  gyro_y_cal /= 2000;                                                  //Divide the gyro_y_cal variable by 2000 to get the avarage offset
  gyro_z_cal /= 2000;
 Serial.println(" Gyro Offset calcutated: " ); 
  for (int cal_int2 = 0; cal_int2 < 2000 ; cal_int2 ++){                  //Run this code 2000 times
    if(cal_int2 % 125 == 0)Serial.print(".");                              //Print a dot on the LCD every 125 readings
    mpu_read_data();                                             //Read the raw acc and gyro data from the MPU-6050
    acc_x_cal += acc_x;                                              //Add the gyro x-axis offset to the gyro_x_cal variable
    acc_y_cal += acc_y;                                              //Add the gyro y-axis offset to the gyro_y_cal variable
    acc_z_cal += acc_z;                                              //Add the gyro z-axis offset to the gyro_z_cal variable
    delay(3);                                                          //Delay 3us to simulate the 250Hz program loop
  }
  acc_x_cal /= 2000;                                                  //Divide the gyro_x_cal variable by 2000 to get the avarage offset
  acc_y_cal /= 2000;                                                  //Divide the gyro_y_cal variable by 2000 to get the avarage offset
  acc_z_cal /= 2000;
 
  Serial.println("IMU Setup Complete");
  }
  }
  void mpu_read_data(){
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(true);
    Wire.beginTransmission(MPU_ADDR);
    Wire.requestFrom(MPU_ADDR, 14, true); // request a total of 14 registers
    acc_x = Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    acc_y = Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    acc_z = Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tp = Wire.read()<<8|Wire.read(); // 0x41 (TEMP_OUT_H) &  0x42 (TEMP_OUT_L)
    gyro_x = Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    gyro_y = Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    gyro_z = Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)                                               //Subtract the offset calibration value from the raw gyro_z value
  }

  void serial_print(){    
//    gyro_x -= gyro_x_cal;                                                //Subtract the offset calibration value from the raw gyro_x value
//    gyro_y -= gyro_y_cal;                                                //Subtract the offset calibration value from the raw gyro_y value
//    gyro_z -= gyro_z_cal;
//    
//    Serial.print(acc_x); Serial.print(" , ");
//    Serial.print(acc_y); Serial.print(" , ");
//    Serial.print(acc_z); Serial.print(" , ");
//    Serial.print(gyro_x); Serial.print(" , ");
//    Serial.print(gyro_y); Serial.print(" , ");
//    Serial.print(gyro_z); Serial.print(" , ");
      Serial.print(angle_pitch_output); Serial.print(" , ");
//      Serial.print(angle_roll_output); Serial.print(" , ");
//      Serial.print(angle_yaw_output); Serial.print(" , ");
    //Serial.print(Tp); 
    //Serial.println(" ");


  }
  void mpu_process(long double elapsedtime){
    gyro_x -= gyro_x_cal;                                                //Subtract the offset calibration value from the raw gyro_x value
    gyro_y -= gyro_y_cal;                                                //Subtract the offset calibration value from the raw gyro_y value
    gyro_z -= gyro_z_cal;

    acc_x -= acc_x_cal;                                                //Subtract the offset calibration value from the raw gyro_x value
    acc_y -= acc_y_cal;                                                //Subtract the offset calibration value from the raw gyro_y value
    acc_z -= acc_z_cal;
    acc_z =+ 4096;

    angle_pitch += gyro_x *  0.01527*elapsedtime;                                   //Calculate the traveled pitch angle and add this to the angle_pitch variable
    angle_roll += gyro_y * 0.01527*elapsedtime;                                    //Calculate the traveled roll angle and add this to the angle_roll variable
    angle_yaw += gyro_z * 0.01527*elapsedtime;

    angle_pitch += angle_roll * sin(gyro_z *  0.000266*elapsedtime);               //If the IMU has yawed transfer the roll angle to the pitch angel
    angle_roll -= angle_pitch * sin(gyro_z * 0.000266*elapsedtime);               //If the IMU has yawed transfer the pitch angle to the roll angel

    acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));  //Calculate the total accelerometer vector
    //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
    angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296*2;       //Calculate the pitch angle
    angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296*2;       //Calculate the roll angle
//      angle_roll_acc = atan2((float)acc_y, (float)acc_z)* 57.296*2;
//      angle_pitch_acc = atan2((float)acc_x, sqrt(acc_y*acc_y + acc_z*acc_z))*57.296*2;

    angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
    angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll

    
  if(set_gyro_angles){                                                 //If the IMU is already started
    angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
    angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
  }
  else{
    angle_pitch = angle_pitch_acc;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle 
    angle_roll = angle_roll_acc;                                       //Set the gyro roll angle equal to the accelerometer roll angle 
    set_gyro_angles = true;
  }
  gyro_pitch = gyro_x* 0.0153;
  gyro_pitch = 0.9998*gyro_pitch + angle_pitch_acc*0.0002;
  
   angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1;   //Take 90% of the output pitch value and add 10% of the raw pitch value
   angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1;      //Take 90% of the output roll value and add 10% of the raw roll value
   angle_yaw_output = angle_yaw_output*0.9 + angle_yaw*0.1;
 }
};

MPU_6050 IMU;
