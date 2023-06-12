#include "Arduino.h"
#include "STEPPER_interface.h"
#include "STEPPER_config.h"
#include "STEPPER_private.h"

void STEPPER_INIT_THREEMOTOR()
{
  SPEEDPERREV = STEPS_PER_REV;
  STEPPIN1 = STEP_PIN1;
  DIRECTIONPIN1 = DIRECTION_PIN1;
  STEPPIN2 = STEP_PIN2;
  DIRECTIONPIN2 = DIRECTION_PIN2;
  STEPPIN3 = STEP_PIN3;
  DIRECTIONPIN3 = DIRECTION_PIN3;

  pinMode(DIRECTIONPIN1, OUTPUT);
  pinMode(DIRECTIONPIN2, OUTPUT);
  pinMode(DIRECTIONPIN3, OUTPUT);
  pinMode(STEPPIN1, OUTPUT);
  pinMode(STEPPIN2, OUTPUT);
  pinMode(STEPPIN3, OUTPUT);

}

void STEPPER_INIT_ONEMOTOR()
{
  SPEEDPERREV = STEPS_PER_REV;
  STEPPIN3 = STEP_PIN;
  DIRECTIONPIN3 = DIRECTION_PIN;
  pinMode(DIRECTIONPIN3, OUTPUT);
  pinMode(STEPPIN3, OUTPUT);
}

void STEPPER_SPEED(long SPEED_PER_REV)
{
  DELAYTIME = (60000L / (SPEEDPERREV * SPEED_PER_REV));
}

void STEPPER_STEP_INIT(int FORWARD_STEP, int BACKWARD_STEP)
{
  FORWARDSTEP = FORWARD_STEP;
  BACKWARDSTEP = BACKWARD_STEP;
  
}

void STEPPER_STEP_ONEMOTOR(int STEP)
{
    POSITIONMOTORTHREE+=STEP;
    if (STEP >= ZERO)
    {
      digitalWrite(DIRECTIONPIN3, HIGH);
      for (IITERATOR = ZERO; IITERATOR < (STEP * FORWARDSTEP); IITERATOR++)
      {
        digitalWrite(STEPPIN3, HIGH);
        delay(DELAYTIME);
        digitalWrite(STEPPIN3, LOW);
        delay(DELAYTIME);
      }
    }

    else if (STEP < ZERO)
    {
      digitalWrite(DIRECTIONPIN3, LOW);
      for (IITERATOR = ZERO; IITERATOR < -(STEP * BACKWARDSTEP); IITERATOR++)
      {
        digitalWrite(STEPPIN3, HIGH);
        delay(DELAYTIME);
        digitalWrite(STEPPIN3, LOW);
        delay(DELAYTIME);
      }
    }
}

void STEPPER_STEP_TWOMOTOR(int STEP_MOTOR_ONE, int STEP_MOTOR_TWO)
{
    POSITIONMOTORONE+=STEP_MOTOR_ONE;
    POSITIONMOTORTWO+=STEP_MOTOR_TWO;

  if (STEP_MOTOR_ONE >= ZERO && STEP_MOTOR_TWO >= ZERO)
  {
    digitalWrite(DIRECTIONPIN1, HIGH);
    digitalWrite(DIRECTIONPIN2, HIGH);
  }

  else if (STEP_MOTOR_ONE < ZERO && STEP_MOTOR_TWO < ZERO)
  {
    digitalWrite(DIRECTIONPIN1, LOW);
    digitalWrite(DIRECTIONPIN2, LOW);

    STEP_MOTOR_ONE = -STEP_MOTOR_ONE;
    STEP_MOTOR_TWO = -STEP_MOTOR_TWO;
  }

  else if (STEP_MOTOR_ONE < ZERO && STEP_MOTOR_TWO > ZERO)
  {
    digitalWrite(DIRECTIONPIN1, LOW);
    digitalWrite(DIRECTIONPIN2, HIGH);

    STEP_MOTOR_ONE = -STEP_MOTOR_ONE;
  }

  else
  {
    digitalWrite(DIRECTIONPIN1, HIGH);
    digitalWrite(DIRECTIONPIN2, LOW);

    STEP_MOTOR_TWO = -STEP_MOTOR_TWO;
  }

  if (STEP_MOTOR_ONE >= STEP_MOTOR_TWO)
  {
    for (IITERATOR = ZERO; IITERATOR < (STEP_MOTOR_ONE * FORWARDSTEP); IITERATOR++)
    {
      digitalWrite(STEPPIN1, HIGH);
      delay(DELAYTIME);
      digitalWrite(STEPPIN1, LOW);
      if (IITERATOR < STEP_MOTOR_TWO * BACKWARDSTEP)
      {
        delay(DELAYTIME);
        digitalWrite(STEPPIN2, HIGH);
        delay(DELAYTIME);
        digitalWrite(STEPPIN2, LOW);
      }
      delay(DELAYTIME);
    }
  }
  else
  {
    for (IITERATOR = ZERO; IITERATOR < (STEP_MOTOR_TWO * BACKWARDSTEP); IITERATOR++)
    {
      digitalWrite(STEPPIN2, HIGH);
      delay(DELAYTIME);
      digitalWrite(STEPPIN2, LOW);
      if (IITERATOR < STEP_MOTOR_ONE * FORWARDSTEP)
      {
        delay(DELAYTIME);
        digitalWrite(STEPPIN1, HIGH);
        delay(DELAYTIME);
        digitalWrite(STEPPIN1, LOW);
      }
      delay(DELAYTIME);
    }
  }
}

void STEPPER_MICROSTEP_INIT_TWOMOTOR()
{

  pinMode(MOTOR1_M0PIN, OUTPUT);
  pinMode(MOTOR1_M1PIN, OUTPUT);
  pinMode(MOTOR1_M2PIN, OUTPUT);
  pinMode(MOTOR2_M0PIN, OUTPUT);
  pinMode(MOTOR2_M1PIN, OUTPUT);
  pinMode(MOTOR2_M2PIN, OUTPUT);

}

void STEPPER_MICROSTEP_TWOMOTOR(int MICROSTEP1, int MICROSTEP2)
{
  GLOBALMICROSTEPONE = MICROSTEP1;
  GLOBALMICROSTEPTWO = MICROSTEP2;

 for (int c=0; c<=1;c++)
 {
    if (c=0)
    {
      MICROSTEP = MICROSTEP1;
    }
    if (c=1)
    {
      MICROSTEP = MICROSTEP2;
    }    
    switch (MICROSTEP)
    {
      case MODE_FULLSTEP:
          digitalWrite(MOTORONE_M0, LOW);
          digitalWrite(MOTORONE_M1, LOW);
          digitalWrite(MOTORONE_M2, LOW);
      break;

        case MODE_HALFSTEP:
          digitalWrite(MOTORONE_M0, HIGH);
          digitalWrite(MOTORONE_M1, LOW);
          digitalWrite(MOTORONE_M2, LOW);
      break;

      case MODE_DEVBY4STEP:
           digitalWrite(MOTORONE_M0, LOW);
           digitalWrite(MOTORONE_M1, HIGH);
           digitalWrite(MOTORONE_M2, LOW);
      break;

      case MODE_DEVBY8STEP:
           digitalWrite(MOTORONE_M0, HIGH);
           digitalWrite(MOTORONE_M1, HIGH);
           digitalWrite(MOTORONE_M2, LOW);
      break;

      case MODE_DEVBY16STEP:
          digitalWrite(MOTORONE_M0, LOW);
          digitalWrite(MOTORONE_M1, LOW);
          digitalWrite(MOTORONE_M2, HIGH);
      break;
      
      case MODE_DEVBY32STEP:
           digitalWrite(MOTORONE_M0, HIGH);
           digitalWrite(MOTORONE_M1, HIGH);
           digitalWrite(MOTORONE_M2, HIGH);

      default:
          digitalWrite(MOTORONE_M0, LOW);
          digitalWrite(MOTORONE_M1, LOW);
          digitalWrite(MOTORONE_M2, LOW);
      break;
    }
  }
}

void STEPPER_STEP_ONEMOTOR_MS(int MOTOR, int STEP)
{
  switch (MOTOR)
  {
  case MOTOR_ONE:
    STEP = (STEP * GLOBALMICROSTEPONE);
    break;

  case MOTOR_TWO:
    STEP = (STEP * GLOBALMICROSTEPTWO);
    break;

  default:
    break;
  }
  STEPPER_STEP_ONEMOTOR(STEP);
}

void STEPPER_STEP_TWOMOTOR_MS(int STEP_MOTOR_ONE, int STEP_MOTOR_TWO)
{
  STEP_MOTOR_ONE = (STEP_MOTOR_ONE * GLOBALMICROSTEPONE);
  STEP_MOTOR_TWO = (STEP_MOTOR_TWO * GLOBALMICROSTEPTWO);

  STEPPER_STEP_TWOMOTOR(STEP_MOTOR_ONE, STEP_MOTOR_TWO);
}

int STEPPER_GET_POSITION(int MOTOR_NUMBER)
{
  switch (MOTOR_NUMBER)
  {
  case MOTOR_ONE:
    return POSITIONMOTORONE;
    break;
  case MOTOR_TWO:
    return POSITIONMOTORTWO;
    break;
  case MOTOR_THREE:
    return POSITIONMOTORTHREE;
    break;
  }
}

void STEPPER_SLEEP_INIT()
{
pinMode(SLEEP_PIN1, OUTPUT);
pinMode(SLEEP_PIN2, OUTPUT);
pinMode(SLEEP_PIN3, OUTPUT);

}

void STEPPER_ON()
{
digitalWrite(SLEEP_PIN1, LOW);
digitalWrite(SLEEP_PIN2, LOW);
digitalWrite(SLEEP_PIN3, LOW);

}

void STEPPER_OFF()
{
digitalWrite(SLEEP_PIN1, HIGH);
digitalWrite(SLEEP_PIN2, HIGH);
digitalWrite(SLEEP_PIN3, HIGH);
}