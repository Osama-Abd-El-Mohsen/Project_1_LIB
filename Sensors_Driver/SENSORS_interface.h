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

#ifndef SENSORS_interface_h
#define SENSORS_interface_h

//LDR
void SENSORS_LDR_GetRead(int *LDRUP , int *LDRDOWN ,int *LDRRIGHT ,int *LDRLEFT );

//AMPERE Acs712
int SENSORS_ACS712_GetRead();

//DHT11
void SENSORS_DHT11_GetRead(float *HUNIDITY, float *TEMP);
#endif