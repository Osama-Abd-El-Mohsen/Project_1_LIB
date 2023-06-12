/*************************************************************/
/*************************************************************/
/***********    Author :    Osama Abd EL Mohsen    ***********/
/***********                Mazen Atta             ***********/
/***********    File   :	STEPPER_config.h         ***********/
/***********    Nema17 And DRV8825 				   ***********/
/***********    workable with A4988 driver too     ***********/
/***********    Version:    1.00			       ***********/
/*************************************************************/
/*************************************************************/

#ifndef STEPPPER_CONFIG_H_
#define STEPPER_CONFIG_H_

#define LDR1               A0
#define LDR2               A1
#define LDR3               A2
#define LDR4               A3
#define TEMP               A4
#define VOLT               A5
#define AMP                A6


#define STEPS_PER_REV      200
#define STEP_PIN           8
#define DIRECTION_PIN      9

#define STEP_PIN1          8
#define DIRECTION_PIN1     9
#define STEP_PIN2          10
#define DIRECTION_PIN2     11
#define STEP_PIN3          12
#define DIRECTION_PIN3     13

#define MOTOR1_M0PIN      2
#define MOTOR1_M1PIN      3
#define MOTOR1_M2PIN      4
#define MOTOR2_M0PIN      5
#define MOTOR2_M1PIN      6
#define MOTOR2_M2PIN      7

#define SLEEP_PIN1        14
#define SLEEP_PIN2        0
#define SLEEP_PIN3        1


#define UP                 21
#define DOWN               20
#define RIGHT              19
#define LEFT               18
#define OKAY               17
#define BACK               16
#define RESET              15





#endif