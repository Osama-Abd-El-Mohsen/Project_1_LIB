#include "Arduino.h"
// #include "DHT11.h"
#include "SENSORS_interface.h"
#include "SENSORS_private.h"
// #include "..\Project_Driver\PROJECT1_config.h"
#include "PROJECT1_config.h"

// DHT11 dht11(DHT11);

void SENSORS_LDR_GetRead(int *LDRUP, int *LDRDOWN, int *LDRRIGHT, int *LDRLEFT)
{
   *LDRUP = analogRead(LDR1);
   *LDRDOWN = analogRead(LDR2);
   *LDRRIGHT = analogRead(LDR3);
   *LDRLEFT = analogRead(LDR4);
   Serial.println("LU" "\t" "LD" "\t" "LR" "\t" "LL" "\t");
   Serial.print(*LDRUP);
   Serial.print("\t");
   Serial.print(*LDRDOWN);
   Serial.print("\t");
   Serial.print(*LDRRIGHT);
   Serial.print("\t");
   Serial.println(*LDRLEFT);
}

int SENSORS_ACS712_GetRead()
{
   int ADC;
   return ADC = analogRead(AMP);
}

// void SENSORS_DHT11_GetRead(float *HUNIDITY, float *TEMP)
// {
//    *HUNIDITY = dht11.readHumidity();
//    *TEMP = dht11.readTemperature();
//    if (TEMP != -1 && HUNIDITY != -1)
//    {
//       Serial.print("Temperature: \t  Humidity: ");
//       Serial.print(TEMP);
//       Serial.print(" C");
//       Serial.print("\t");
//       Serial.print(HUNIDITY);
//       Serial.println(" %");
//    }
//    else
//    {
//       Serial.println("Error reading data");
//    }
// }