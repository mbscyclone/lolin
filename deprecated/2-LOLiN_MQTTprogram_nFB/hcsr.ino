#include <HCSR04.h>

void hcsr04loop(int x) {
if(hcsrlooptimer>millis()) return;
else hcsrlooptimer=millis()+300;

  UltraSonicDistanceSensor distanceSensor(hcsrT[x], hcsrE[x]);  // Initialize sensor that uses digital pins 13 and 12.
  int distance = distanceSensor.measureDistanceCm();
  //Serial.print(distance);
  //Serial.println(F("cm"));
//Serial.println(abs(edistance[x] - distance));

    if (distance > 3) {
      if (abs(edistance[x] - distance) > 20) {
        PinState[x] = distance;
        edistance[x] = distance;
      }
    }
}