#include <HCSR04.h>
int edistance;
void hcsr04loop(int x)
{
    UltraSonicDistanceSensor distanceSensor(hcsrT, hcsrE);  // Initialize sensor that uses digital pins 13 and 12.


    int distance = distanceSensor.measureDistanceCm();
  
    Serial.print(distance);
    Serial.println(F("cm"));
    if(distance >2){
    if(abs(edistance-distance)>5){PinState[x]=distance;edistance=distance;}
    }
    else PinState[x]= "";
}