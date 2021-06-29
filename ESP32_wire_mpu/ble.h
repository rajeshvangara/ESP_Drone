
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
class ble{
  
  public:
  char type;
  int thrust = 0;
  int pitch = 0;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()){
    type = SerialBT.read();
    Serial.print(type);
  if (type == 'u'){
    if(thrust <600){
      thrust += 10;
    }
    else {
      thrust = 800;      
    }
  }
  else if (type == 'd'){
    if(thrust >5){
     thrust -= 10;  
    }
    else{
      thrust = 0;   
    }
  }
  else if(type == 'm'){
      thrust = 0;  
  }
  else if (type == 'w'){
    if(pitch <20){
     pitch += 1; 
    }
    else{
      pitch = 20;
    } 
  }
  else if (type == 's'){
    if (pitch > -20){
    pitch -= 1;
    }
    else{
      pitch = -20;
    }
  }
  //Serial.print(pitch); Serial.print(" , ");
  //Serial.println(thrust);
  }
}
};
ble ble;
