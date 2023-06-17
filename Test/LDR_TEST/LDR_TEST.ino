#include "STEPPER_interface.h"
#define motor_one_step 8
#define motor_two_step 10
#define motor_there_step 12

#define motor_one_dir 9
#define motor_two_dir 11
#define motor_there_dir 13
#define LDRTR A0
#define LDRTL A1
#define LDRBR A2
#define LDRBL A3

int UP_AVE = 0;
int DOWN_AVE = 0;
int RIGHT_AVE = 0;
int LEFT_AVE = 0;

int TR = 0;
int TL = 0;
int BR = 0;
int BL = 0;

int DIF_VRT = 0;
int DIF_HOR = 0;

int pos = 0;
int k = 0;
void setup() {

  pinMode(LDRTR, INPUT);
  pinMode(LDRTL, INPUT);
  pinMode(LDRBR, INPUT);
  pinMode(LDRBL, INPUT);

  STEPPER_INIT_THREEMOTOR(200, 8, 9, 10, 11, 12, 13);
  STEPPER_SPEED(250);
  Serial.begin(9600);
}

void loop() {
  k = 0;
  Serial.println("========");
  Serial.print("TR = ");
  TR = analogRead(LDRTR);
  Serial.println(TR);
  Serial.print("TL = ");
  TL = analogRead(LDRTL);
  Serial.println(TL);
  Serial.print("BR = ");
  BR = analogRead(LDRBR);
  Serial.println(BR);
  Serial.print("BL = ");
  BL = analogRead(LDRBL);
  Serial.println(BL);
  Serial.println("========");
  UP_AVE = AVE(TR, TL);
  DOWN_AVE = AVE(BR, BL);
  RIGHT_AVE = AVE(TR, BR);
  LEFT_AVE = AVE(TL, BL);
  DIF_HOR = DEF(LEFT_AVE, RIGHT_AVE);
  DIF_VRT = DEF(UP_AVE, DOWN_AVE);

  Serial.println("========");
  Serial.print("UP AVE = ");
  Serial.println(UP_AVE);
  Serial.print("DOWN AVE = ");
  Serial.println(DOWN_AVE);
  Serial.print("RIGHT AVE = ");
  Serial.println(RIGHT_AVE);
  Serial.print("LEFT AVE = ");
  Serial.println(LEFT_AVE);
  Serial.println("========");
  Serial.print("DIF_HOR : ");
  Serial.println(DIF_HOR);
  Serial.print("DIF_VRT : ");
  Serial.println(DIF_VRT);
  Serial.println("========");

  if ((UP_AVE > DOWN_AVE && pos <= 50 * 32) && abs(DIF_VRT) > 40) {
    k = map(DIF_VRT, 0, 1023, 0, 50 * 32);
    Serial.print("UP : ");
    Serial.println(-k);
    Serial.println("========");
    STEPPER_STEP_TWOMOTOR(k, -k);
    pos = STEPPER_GET_POSITION(MOTOR_ONE);
  }

  else if ((UP_AVE < DOWN_AVE && pos <= 50 * 32) && abs(DIF_VRT) > 40) {
    k = map(DIF_VRT, 0, 1023, 0, 50 * 32);
    Serial.print("Down : ");
    Serial.println(-k);
    STEPPER_STEP_TWOMOTOR(k, -k);
    Serial.println("========");
  }

  else if (pos >= 50 * 32) {
    STEPPER_STEP_TWOMOTOR(-pos, pos);
  }

  if ((RIGHT_AVE > LEFT_AVE && pos <= 200 * 32) && abs(DIF_HOR) > 40) {
    k = map(DIF_HOR, 0, 1023, 0, 200 * 32);
    Serial.print("Left : ");
    Serial.println(-k);
    Serial.println("========");
    STEPPER_STEP_ONEMOTOR(k);
  }

  else if ((RIGHT_AVE < LEFT_AVE && pos <= 200 * 32) && abs(DIF_HOR) > 40) {
    k = map(DIF_HOR, 0, 1023, 0, 200 * 32);
    Serial.print("Right : ");
    Serial.println(-k);
    Serial.println("========");
    STEPPER_STEP_ONEMOTOR(k);
  } else if (pos >= 200 * 32) {
    STEPPER_STEP_ONEMOTOR(-pos);
  }
  delay(1000);
}

int AVE(int VALUE_ONE, int VALUE_TWO) {
  return ((VALUE_ONE + VALUE_TWO) / 2);
}


int DEF(int VALUE_ONE, int VALUE_TWO) {
  return ((VALUE_ONE - VALUE_TWO));
}






