// https://github.com/ElectronicCats/mpu6050/blob/master/examples/MPU6050_raw/MPU6050_raw.ino
/* Code written by Goncalo Martins for ENCE 3210 Microprocessors. Loop code edited by Aidan Donnellan */

#include "MPU6050.h"

MPU6050 gMPU;
int16_t gAx, gAy, gAz;

void setup() {
  Serial.begin(115200);

  // Init IMU
  gMPU.initialize();

}

void loop() {

  gMPU.getAcceleration(&gAx, &gAy, &gAz);
  Serial.print("gAx: ");
  Serial.println(gAx);
  Serial.print("gAy: ");
  Serial.println(gAy);
  Serial.print("gAz: ");
  Serial.println(gAz);


}
