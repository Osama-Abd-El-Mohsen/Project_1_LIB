#include "FL2S_interface.h"
#define motor_one_step  13
#define motor_two_step  10
#define motor_there_step  8

#define motor_one_dir  12
#define motor_two_dir  11
#define motor_there_dir  9

void setup()
{
  STEPPER_INIT(200, motor_one_step , motor_one_dir,motor_two_step,motor_two_dir);
  STEPPER_SPEED(10);
  Serial.begin(9600);


}

void loop()
{
   STEPPER_STEP(20, -20);
  delay(800);
  STEPPER_STEP(-40, 40);
  delay(800);

  int pos1 = STEPPER_GET_POSITION(1);
  int pos2 = STEPPER_GET_POSITION(2);
  Serial.print("Motor One Position : ");
  Serial.println(pos1);
  Serial.print("Motor Two Position : ");
  Serial.println(pos2);
}

