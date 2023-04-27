/*************************************************************/
/*************************************************************/
/***********    Author :    Osama Abd EL Mohsen    ***********/
/***********                Mazen Atta             ***********/
/***********    File   :	FL2S_private.h         ***********/
/***********    Nema17 And DRV8825 				   ***********/
/***********    workable with A4988 driver too     ***********/
/***********    Version:    1.00			       ***********/
/*************************************************************/
/*************************************************************/

#ifndef FL2S_PRIVATE_H_
#define FL2S_PRIVATE_H_

int SPEEDPERREV;
int STEPPIN1;
int DIRECTIONPIN1;
int STEPPIN2;
int DIRECTIONPIN2;
int STEPPIN3;
int DIRECTIONPIN3;
int FORWARDSTEP = 1;
int BACKWARDSTEP = 1;
int STATE;
unsigned long DELAYTIME;
int MICROSTEP;
int MOTORONE_M0;
int MOTORONE_M1;
int MOTORONE_M2;
int MOTORTWO_M0;
int MOTORTWO_M1;
int MOTORTWO_M2;
int GLOBALMICROSTEPONE;
int GLOBALMICROSTEPTWO;
int IITERATOR;
int POSITIONMOTORONE = 0;
int POSITIONMOTORTWO = 0;
int POSITIONMOTORTHREE = 0;


#endif