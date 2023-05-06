/*************************************************************/
/*************************************************************/
/***********    Author :    Osama Abd EL Mohsen    ***********/
/***********                Mazen Atta             ***********/
/***********    File   :	FL2S_interface.h       ***********/
/***********    Nema17 And DRV8825 				   ***********/
/***********    workable with A4988 driver too     ***********/
/***********    Version:    1.00			       ***********/
/*************************************************************/
/*************************************************************/

#ifndef STEPPER_interface_h
#define STEPPER_interface_h

#define MODE_FULLSTEP    1
#define MODE_HALFSTEP    2
#define MODE_DEVBY4STEP  4
#define MODE_DEVBY8STEP  8
#define MODE_DEVBY16STEP 16
#define MODE_DEVBY32STEP 32
#define MOTOR_ONE 1
#define MOTOR_TWO 2
#define MOTOR_THREE 3
#define ZERO      0

////////////////////////////////////////////////*INIT*///////////////////////////////////////////////////
/*************************************  INIT MOTOR DRIVER PINS  ***************************************/
////////////////////////////////////////////////*INIT*/////////////////////////////////////////////////
/*
    STEPPER_STEP_INIT(int FORWARD_STEP, int BACKWARD_STEP);
    Use it if you want customize FORWARD_STEP steps and BACKWARD_STEP
    EX : STEPPER_STEP_INIT(2, 3);
    motor will jump 2 stpes in forward and 3 steps backward
*/
void STEPPER_STEP_INIT(int FORWARD_STEP, int BACKWARD_STEP);

/*
void STEPPER_INIT(int STEPS_PER_REV, int STEP_PIN1, int DIRECTION_PIN1, int STEP_PIN2, int DIRECTION_PIN2, int STEP_PIN3, int DIRECTION_PIN3);
    Use it to set steps per revlution of motor and to init Pins For (THREE MOTORS)
    EX : STEPPER_INIT(200, 10, 11, 12, 13, 14, 15);
*/
void STEPPER_INIT_THREEMOTOR(int STEPS_PER_REV, int STEP_PIN1, int DIRECTION_PIN1, int STEP_PIN2, int DIRECTION_PIN2, int STEP_PIN3, int DIRECTION_PIN3);

/*
    STEPPER_INIT_ONEMOTOR(int STEPS_PER_REV, int STEP_PIN1, int DIRECTION_PIN1);
    Use it to set steps per revlution of motor and to init DRV8825 Pins For only (ONE MOTOR)
    EX : STEPPER_INIT_ONEMOTOR(200, 10, 11);
*/
void STEPPER_INIT_ONEMOTOR(int STEPS_PER_REV, int STEP_PIN1, int DIRECTION_PIN1);

/*
void STEPPER_MICROSTEP_INIT(int MOTOR1_M0PIN, int MOTOR1_M1PIN, int MOTOR1_M2PIN, int MOTOR2_M0PIN, int MOTOR2_M1PIN, int MOTOR2_M2PIN);
    Use it to setup microstep in motor for two motors together
    EX : STEPPER_MICROSTEP_INIT(1, 2, 3, 4, 5, 6);
    motors now are ready to use microstep
*/
void STEPPER_MICROSTEP_INIT_TWOMOTOR(int MOTOR1_M0PIN, int MOTOR1_M1PIN, int MOTOR1_M2PIN, int MOTOR2_M0PIN, int MOTOR2_M1PIN, int MOTOR2_M2PIN);

/*
    STEPPER_SPEED(long SPEED_PER_REV);
    Use it to set speed per revlution/min of motor 
    EX : STEPPER_SPEED(10);
    motor will move by speed 10 rev/min 
*/
void STEPPER_SPEED(long SPEED_PER_REV);

///////////////////////////////////////////////*MOVING*//////////////////////////////////////////////////
/************************************  FUNCTIONS TO MOVE MOTORS  **************************************/
///////////////////////////////////////////////*MOVING*////////////////////////////////////////////////
/*
    STEPPER_STEP(int STEP_MOTOR_ONE, int STEP_MOTOR_TWO);
    Use it to start moving the motor by steps 
    you can use it to move the two motors together
    EX : STEPPER_STEP(200, -200)
    first motor will move 200 steps CW
    second one  will move 200 steps CCW
*/
void STEPPER_STEP_TWOMOTOR(int STEP_MOTOR_ONE, int STEP_MOTOR_TWO);


/*
    STEPPER_STEP_ONEMOTOR(int MOTOR, int STEP);
    Use it to start moving the only one motor by steps 
    EX : STEPPER_STEP_ONEMOTOR(1, -200)
    motor number 1 will move 200 steps CCW
*/
void STEPPER_STEP_ONEMOTOR(int STEP);


//////////////////////////////////////////////*MICRO STEP*///////////////////////////////////////////////
/************************************  FUNCTIONS TO USE MICROSTEP  ************************************/
//////////////////////////////////////////////*MICRO STEP*/////////////////////////////////////////////
/*
    STEPPER_MICROSTEP(int MOTOR, int MICROSTEP);
    Use it to setup microstep in motor for only one motor
    and u can use one of the following modes :
        MODE_FULLSTEP    
        MODE_HALFSTEP    
        MODE_DEVBY4STEP  
        MODE_DEVBY8STEP  
        MODE_DEVBY16STEP 
        MODE_DEVBY32STEP 

    EX : STEPPER_MICROSTEP(1,MODE_DEVBY4STEP);
    motor 1 will move 1/4 step every time 
    NOTE: if u used STEPPER_STEP() func and want to move 200 steps u have to but steps as 200*4 here
    or just use STEPPER_STEP_MS() func
*/
void STEPPER_MICROSTEP_TWOMOTOR(int MICROSTEP1, int MICROSTEP2);


/*
    STEPPER_STEP_MS(int STEP_MOTOR_ONE, int STEP_MOTOR_TWO);
    looks like STEPPER_STEP() func
    Use it to set steps for the motor which useing microstep
    EX : STEPPER_STEP_MS(200, int -200);
    motors one will move 200 step with microstep as EX : if  microstep in divby4 
    then the motor will step 200 step not only 50
*/
void STEPPER_STEP_TWOMOTOR_MS(int STEP_MOTOR_ONE, int STEP_MOTOR_TWO);

/*
    STEPPER_STEP_ONEMOTOR_MS(int MOTOR, int STEP);
    EX : STEPPER_STEP_ONEMOTOR_MS(1,200);
    the same as  STEPPER_STEP_ONEMOTOR() func but 
    doing the same as STEPPER_STEP_MS()
*/
void STEPPER_STEP_ONEMOTOR_MS(int MOTOR, int STEP);

int STEPPER_GET_POSITION(int MOTOR_NUMBER);
#endif