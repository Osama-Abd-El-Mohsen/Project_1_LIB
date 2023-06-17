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

/*LDR Function*/
/*Getting Four readings for four ldrs bu passing variable address */
void SENSORS_LDR_GetRead(int *LDRUP , int *LDRDOWN ,int *LDRRIGHT ,int *LDRLEFT );

/*ACS712 Function*/
/*Returning ACS712 current sensor reading */
int SENSORS_ACS712_GetRead();

/*DHT11 Function*/
/*Getting DHT11 HUNIDITY & TEMPERATURE  */
void SENSORS_DHT11_GetRead(float *HUNIDITY, float *TEMP);
#endif